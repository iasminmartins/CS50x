from cs50 import get_int


def main():
    height = 0
    # Ensure valid input for the height
    while height < 1 or height > 8:
        height = get_int("Height: ")

    # Make double pyramid
    pyramid(height)


def pyramid(height):

    # Prints a double pyramid

    for i in range(height):
        print(" " * (height - i - 1), end="")  # Print spaces before the hashes
        print("#" * (i + 1), end="")  # Print hashes for the first side of pyramid
        print("  ", end="")  # Double space gap
        print("#" * (i + 1))  # Print hashes for the second side of the pyramid


# Call main to execute code
main()
