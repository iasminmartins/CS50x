from cs50 import get_int
import re

def main():
    card_number = get_int("Number: ");
    print(kind_of_card(card_number))


def kind_of_card(n):
# Regex to determine credit card type

    visa_pattern = r"^4\d{12}(\d{3})?(\d{3})?$"  # VISA cards start with 4 and can be 13 or 16 digits
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
