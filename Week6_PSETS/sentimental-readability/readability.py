from cs50 import get_string


def main():

    # Prompt user for a non-empty string
    while True:
        text = get_string("Text: ")
        # Verify string is not empty & void of just spaces
        if text.strip():
            break

    # Count the letters, words, and sentences in text
    letters = countLetters(text)
    words = countWords(text)
    sentences = countSentences(text)

    # Calculate letters & sentences per 100 words
    lettersCalc = (letters / words) * 100
    sentencesCalc = (sentences / words) * 100

    # Compute the Coleman-Liau Index & round to nearest int
    coleIndex = round(0.0588 * lettersCalc - 0.296 * sentencesCalc - 15.8)

    # Print grade level
    if (coleIndex < 1):
        print("Before Grade 1")
    elif coleIndex > 15:
        print("Grade 16+")
    else:
        print(f"Grade {coleIndex}")


def countLetters(text):
    # Variable to hold count
    count = 0

    # Remove any trailing whitespace
    text = text.strip()

    # Loop over string counting letters
    for i in range(len(text)):
        if text[i].isalpha():
            count += 1

    return count


def countWords(text):
    # Variable to hold count
    # Initalize to 1 for first word
    count = 1

    # Remove trailing whitespace
    text = text.strip()

    # Loop over string counting spaces
    for i in range(len(text)):
        if text[i].isspace():
            count += 1

    return count


def countSentences(text):
    # Variable to hold count
    count = 0

    # Count any periods
    count += text.count(".")

    # Count any exclmation points
    count += text.count("!")

    # Count any question marks
    count += text.count("?")

    return count


main()
