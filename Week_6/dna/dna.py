import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py csvfile.csv dnatext.txt")

    # TODO: Read database file into a variable
    database = []
    sequence_types = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        sequence_types = reader.fieldnames
        for row in reader:
            database.append(row)
    # TODO: Read DNA sequence file into a variable
    sequences = []
    with open(sys.argv[2], encoding="utf-8") as file:
        sequences = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    longestMatches = {}
    for sequence in sequence_types:
        if sequence != "name":
            longestMatches[sequence] = longest_match(sequences, sequence)

    # TODO: Check database for matching profiles
    for entry in database:
        isValid = True
        for sequence, max_num in longestMatches.items():
            if int(entry[sequence]) != max_num:
                isValid = False
                break
        if isValid == True:
            print(entry["name"])
            break

    if isValid == False:
        print("No match")

    return


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

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
