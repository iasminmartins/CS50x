from cs50 import get_string

def main():
    text = get_string("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    clindex = coleman_liau_index(letters, words, sentences)

    if clindex < 1:
        print("Before Grade 1")
    elif clindex >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {clindex}")


def count_letters(text):
    # Counts alphabetical characters
    sum = 0
    for char in text:
        if char.isalpha():
            sum += 1
    return sum


def count_words(text):
    words = text.split()  # Create list of words
    return len(words)


def count_sentences(text):
    count = 0
    for char in text:
        if char in ['.', '!', '?']:
            count += 1
    return count


def coleman_liau_index(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)
    return index


if __name__ == "__main__":
    main()
