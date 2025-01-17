from cs50 import get_string


def main():
    # Get input text from user
    text = get_string("Text: ")

    # Count letters, words, and sentences in the text
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    
    # Calculate Coleman-Liau index
    clindex = coleman_liau_index(letters, words, sentences)

    # Print the grade level based on the Coleman-Liau index
    if clindex < 1:
        print("Before Grade 1")
    elif clindex >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {clindex}")


def count_letters(text):
    # Counts alphabetical characters in text
    sum = 0
    for char in text:
        if char.isalpha():
            sum += 1
    return sum


def count_words(text):
    # Splits the text into words and returns the word count
    words = text.split()  # Create list of words by splitting at whitespace
    return len(words)


def count_sentences(text):
    # Counts the number of sentence-ending punctuation marks (., !, ?)
    count = 0
    for char in text:
        if char in ['.', '!', '?']:
            count += 1
    return count


def coleman_liau_index(letters, words, sentences):
    # Calculates the Coleman-Liau index for readability
    L = (letters / words) * 100    # Average number of letters per 100 words
    S = (sentences / words) * 100    # Average number of sentences per 100 words
    index = round(0.0588 * L - 0.296 * S - 15.8)    # Coleman-Liau formula
    return index

# Run the program if this file is executed directly
if __name__ == "__main__":
    main()
