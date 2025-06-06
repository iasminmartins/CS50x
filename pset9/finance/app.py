import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd
import datetime

# Configure application
app = Flask(__name__)

# Custom filter for currency format
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Disable caching for responses"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Display user's stock portfolio"""

    # Get the current user's cash balance
    user_id = session["user_id"]
    cash_query = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

    if not cash_query or len(cash_query) != 1:
        return apology("Unable to fetch user data", 500)

    user_cash = cash_query[0]["cash"]

    # Query the user's stock portfolio
    stocks = db.execute("""
        SELECT symbol, SUM(shares) AS shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING shares > 0
    """, user_id)  # Filter out stocks where total_shares <= 0

    stock_data = []
    grand_total = user_cash

    # Fetch real-time stock prices and calculate totals
    for stock in stocks:
        symbol = stock["symbol"]
        total_shares = stock["shares"]

        stock_info = lookup(symbol)
        if not stock_info:
            return apology(f"Could not fetch data for symbol {symbol}", 400)

        price = stock_info["price"]
        total_value = total_shares * price

        # Add stock details to the portfolio data
        stock_data.append({
            "symbol": symbol,
            "shares": total_shares,
            "price": price,
            "total_value": total_value
        })

        # Update the grand total with the stock's current value
        grand_total += total_value

    return render_template(
        "index.html",
        stock_data=stock_data,
        cash=user_cash,
        grand_total=grand_total
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Shares must be a number")

        if not symbol:
            return apology("Must provide stock symbol")

        stock = lookup(symbol.upper())

        if stock is None:
            return apology("Invalid stock symbol")

        if shares < 0:
            return apology("Must provide a positive number of shares", 400)

        total_cost = shares * stock["price"]

        user_id = session["user_id"]
        user_cash_query = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        user_cash = user_cash_query[0]["cash"]

        if total_cost > user_cash:
            return apology("Not enough cash")

        update_cash = user_cash - total_cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_cash, user_id)

        date = datetime.datetime.now()

        # Insert into the transactions table with the CURRENT_DATE for transaction_date
        db.execute("""
            INSERT INTO transactions (user_id, symbol, shares, price, transaction_date)
            VALUES (?, ?, ?, ?, ?)
        """, user_id, stock["symbol"], shares, stock["price"], date)

        flash(f"Transaction completed successfully! {shares} shares of {symbol} were bought!")

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]

    transactions = db.execute("""
        SELECT symbol, shares, price, transaction_date
        FROM transactions
        WHERE user_id = ?
        ORDER BY transaction_date DESC
    """, user_id)

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote (current price)."""

    if request.method == "GET":
        return render_template("quote.html")

    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must provide symbol")

        # Look up stock
        stock = lookup(symbol.upper())
        if stock is None:
            return apology("Invalid symbol")

        # If stock found
        return render_template("quoted.html", stock=stock)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("Must provide username")

        password = request.form.get("password")
        if not password:
            return apology("Must provide password")

        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("Must confirm password")

        if password != confirmation:
            return apology("Passwords don't match")

        # User insertion
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                       username, generate_password_hash(password))
        except ValueError:
            # Username already exists
            return apology("username already exists")

        # Automatic login after registration
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]

    if request.method == "GET":
        # Query the user's current stock portfolio
        stocks = db.execute("""
            SELECT symbol, SUM(shares) AS total_shares
            FROM transactions
            WHERE user_id = ?
            GROUP BY symbol
            HAVING total_shares > 0
        """, user_id)

        if not stocks:
            return apology("You don't own any stocks to sell.")

        return render_template("sell.html", stocks=stocks)

    elif request.method == "POST":
        # Validate form inputs
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must provide stock symbol")

        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Shares must be a number")

        if shares <= 0:
            return apology("Must provide a positive number of shares")

        # Validate stock symbol
        stock = lookup(symbol.upper())
        if stock is None:
            return apology("Invalid stock symbol")

        # Check if the user owns the stock and has enough shares
        user_shares_query = db.execute("""
            SELECT SUM(shares) AS total_shares
            FROM transactions
            WHERE user_id = ? AND symbol = ?
            GROUP BY symbol
        """, user_id, symbol)

        if not user_shares_query or user_shares_query[0]["total_shares"] < shares:
            return apology("Not enough shares to sell")

        # Calculate total value of the sale
        total_sale_value = shares * stock["price"]

        # Update user's cash balance
        db.execute("""
            UPDATE users
            SET cash = cash + ?
            WHERE id = ?
        """, total_sale_value, user_id)

        # Record the sale in transactions (negative shares to indicate sale)
        db.execute("""
            INSERT INTO transactions (user_id, symbol, shares, price, transaction_date)
            VALUES (?, ?, ?, ?, CURRENT_TIMESTAMP)
        """, user_id, symbol.upper(), -shares, stock["price"])

        flash(f"Successfully sold {shares} shares of {symbol.upper()}!")

        return redirect("/")


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """Allow user to change password"""

    if request.method == "POST":
        user_id = session["user_id"]

        current_password = request.form.get("current_password")
        new_password = request.form.get("new_password")
        confirmation = request.form.get("confirmation")
        if not current_password or not new_password or not confirmation:
            return apology("All fields must be filled")

        user = db.execute("SELECT hash FROM users WHERE id = :user_id", user_id=user_id)
        if len(user) != 1 or not check_password_hash(user[0]["hash"], current_password):
            return apology("Incorrect current password")

        if new_password != confirmation:
            return apology("Passwords do not match")

        db.execute("UPDATE users SET hash = :hash WHERE id = :user_id",
                   hash=generate_password_hash(new_password), user_id=user_id)

        flash("Password updated successfully!")
        return redirect("/")

    return render_template("change_password.html")
