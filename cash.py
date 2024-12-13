from cs50 import get_float


def main():

    change = -1
    while change < 0:
        change = get_float("Change owed: ")

    # Converts dollars to cents
    cents = round(change * 100)

    print(calculate_coins(cents))


def calculate_coins(n):
    # Calculate minimum number of coins needed

    # Coin values
    coins = [25, 10, 5, 1]
    total = 0

    for coin in coins:
        total += n // coin
        n %= coin

    return total


# Execute program
main()
