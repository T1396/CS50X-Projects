from cs50 import get_string
import re


def main():
    inputText = input("Text: ")

    num_sentences = inputText.count(".") + inputText.count("?") + inputText.count("!")
    num_words = get_number_of_words(inputText)
    chars = re.findall(r'[a-zA-Z]', inputText)
    num_chars = len(chars)

    avg_letters = (num_chars / num_words) * 100
    avg_sentences = (num_sentences / num_words) * 100

    cole_index = (0.0588 * avg_letters) - (0.296 * avg_sentences) - 15.8

    if cole_index < 1:
        print("Before Grade 1")
        exit
    elif cole_index < 16:
        index = int(cole_index+0.5)
        print("Grade " + str(index))
        exit
    else:
        print("Grade 16+")
        exit


def get_number_of_words(input):
    countWords = 0
    for char in range(1, len(input)):
        if input[char-1].isalpha():
            if input[char] == " " or input[char] == "!" or input[char] == "," or input[char] == "." or input[char] == ";" or input[char] == "?":
                countWords += 1

    return countWords


if __name__ == "__main__":
    main()
