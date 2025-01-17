import csv
import sys


def main():

    # Ensure the correct number of command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py database.csv sequence.txt")
        sys.exit(1)

    # Get filenames from command-line arguments
    database_filename = sys.argv[1]
    sequence_filename = sys.argv[2]

    # Read database file and store as a list of dictionaries
    with open(database_filename, "r") as file:
        reader = csv.DictReader(file)
        database = []
        for row in reader:    # Read each row into the database
            database.append(row)

    # Read DNA sequence file into a variable
    with open(sequence_filename, "r") as sequence_file:
        dna_sequence = sequence_file.read()  # Get the entire sequence

    # Find longest match of each STR in DNA sequence
    str_names = list(database[0].keys())
    str_names.remove('name')  # Remove 'name' as it is not an STR
    str_counts = {}  # Create dictionary
    for str_name in str_names:
        str_counts[str_name] = longest_match(dna_sequence, str_name)

    # Check database for matching profiles
    for person in database:
        match = True
        for str_name in str_names:
            # Compare the STR values
            if int(person[str_name]) != str_counts[str_name]:
                # If values don't match
                match = False
                break
        # If match is found
        if match:
            print(person['name'])
            return
    # If no match is found
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Continue checking for consecutive subsequences
        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring, increase the count
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # Return the longest consecutive run found
    return longest_run

# Execute main function
main()
