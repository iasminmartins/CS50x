from cs50 import get_float


def main():
    # Prompt the user for a positive amount of change
    change = -1
    while change < 0:
        change = get_float("Change owed: ")

    # Converts dollars to cents
    cents = round(change * 100)

    # Output the minimum number of coins needed for the change
    print(calculate_coins(cents))


def calculate_coins(n):
    # Calculate minimum number of coins needed for given amount in cents

    # Coin values in cents
    coins = [25, 10, 5, 1]
    total = 0

    # Iterate over each coin
    for coin in coins:
        total += n // coin    # Add the number of coins of this denomination
        n %= coin    # Update remaining cents

    return total


# Execute program
main()
