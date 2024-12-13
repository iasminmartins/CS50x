from cs50 import get_int
import re


def main():
    card_number = get_int("Number: ")
    if luhns(card_number):
        print(kind_of_card(card_number))
    else:
        print("INVALID")


def luhns(n):

    sum = 0
    counter = 0
    # Loop through digits in reverse
    while n > 0:
        last_digit = n % 10  # Get last digit
        n //= 10  # Remove last digit

        # Double every second digit starting from the right
        if counter % 2 == 1:
            doubled = last_digit * 2
            if doubled > 9:
                sum += doubled - 9
            else:
                sum += doubled
        else:
            sum += last_digit

        counter += 1

    # Valid if total sum modulo 10 is 0
    return sum % 10 == 0


def kind_of_card(n):
    # Regex to determine credit card type

    # VISA cards start with 4 and can be 13 or 16 digits
    visa_pattern = r"^4\d{12}(\d{3})?(\d{3})?$"
    mastercard_pattern = r"^5[1-5]\d{14}$"  # MASTERCARD starts with 51-55 and is 16 digits
    amex_pattern = r"^3[47]\d{13}$"  # AMEX cards start with 34 or 37 and are 15 digits

    # Convert int to string because 're.match' expects string
    n = str(n)

    # Match card number and patterns
    if re.match(visa_pattern, n):
        return "VISA"
    elif re.match(mastercard_pattern, n):
        return "MASTERCARD"
    elif re.match(amex_pattern, n):
        return "AMEX"
    else:
        return "INVALID"


if __name__ == "__main__":
    main()
