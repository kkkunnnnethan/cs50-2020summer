from cs50 import get_string
import re

def main():

    input = get_string("Text: ")
    letters = count_letters(input)
    words = count_words(input)
    sentences = count_sentences(input)

    L = letters / words * 100
    S = sentences / words * 100

    index = round(0.0588 * L - 0.296 * S - 15.8)
    if (index >= 16) :
        print("Grade: 16+")
    elif (index < 1) :
        print("Before grade one")
    else :
        print(f"Grade: {index}")
    return 0

def count_letters(s) :
    count = 0
    for i in range(len(s)) :
        if re.match('[a-zA-Z]', s[i]) :
            count += 1
    return count

def count_words(s) :
    return len(s.split())

def count_sentences(s) :
    count = 0
    for i in range(len(s)) :
        if s[i] == "?" or s[i] == "!" or s[i] == "." :
            count += 1
    return count

main()