from cs50 import get_int

def main():
    height = 0
    # Ensure valid input
    while height < 1 or height > 8:
         try:
            height = get_int("Height: ")
        except ValueError:
            print("Invalid input")

    # Make pyramid
    pyramid(height)


def pyramid(height):

    # Prints a right-aligned pyramid
    for i in range(height):
        print(" " * (height - i - 1), end="") # Print spaces before the hashes
        print("#" * (i + 1)) # Print hashes

# Call main to execute code
main()
