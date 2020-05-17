from cs50 import *


def main():
    readability(get_string("Text:"))


def readability(text):
    letters = countLettersOfAnString(text)
    words = countWordsOfAnString(text)
    sentences = countSentencesOfAnString(text)
    index = calculateIndex(letters, words, sentences)

    printGrade(index)


def countLettersOfAnString(text):
    letters = 0

    for i in range(len(text)):
        if (text[i].isalpha()):
            letters += 1

    return letters


def countWordsOfAnString(text):
    spaces = 0

    for i in range(len(text)):
        if (text[i] == ' '):
            spaces += 1

    return spaces + 1


def countSentencesOfAnString(text):
    sentences = 0

    for i in range(len(text)):
        if (text[i] == '.' or text[i] == '!' or text[i] == '?'):
            sentences += 1

    return sentences


def calculateIndex(letters, words, sentences):
    L = (letters / words) * 100
    S = (sentences / words) * 100

    idx = (0.0588 * L - 0.296 * S - 15.8)

    return round(idx)


def printGrade(index):
    if (index < 0):
        print("Before Grade 1")

    elif (index > 16):
        print("Grade 16+")

    else:
        print(f"Grade {index}")


main()