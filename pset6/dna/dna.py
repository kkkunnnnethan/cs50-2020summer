from sys import argv, exit
import csv
# run program --> python dna.py databases/small.csv sequences/1.txt
# run program --> python dna.py databases/large.csv sequences/5.txt


def main():
    profile_list = []  # store everyone's profile into a list

    if len(argv) != 3:
        print("missing command-line argument")
        exit(1)

    with open(argv[1]) as profile:
        p = csv.reader(profile)
        code = next(p)  # read first row of data from profile
        code = code[1:]
        for row in p:
            profile_list.append(row)  # append the rest of data from profile into profile_list

    with open(argv[2]) as database:
        d = csv.reader(database)
        dna = "".join(next(d))  # convert list into string

    result = find_consecutive(code, dna)
    number = list(result.values())  # we only care about numbers when comparing
    answer = ""

    for figure in profile_list:
        index = 0
        if check(number, figure, index):
            answer = ''.join(figure[0:1])
            break

    if len(answer) != 0:
        print(answer)
    else:
        print("No match")

    exit(0)


def find_consecutive(code, dna):
    #  This function find consecutive number of each DNA sequence inside the whole DNA from different person
    result = {}  # store {key-->sequence: value-->consecutive number} into dictionary

    for c in code:
        temp = 0
        count = 0
        code_length = len(c)
        dna_length = len(dna)
        n = 0

        while n < dna_length:
            if n + code_length >= dna_length:
                break

            if c[0: code_length] == dna[n: n + code_length]:
                temp += 1

                if next_is_consecutive(c, dna, code_length, n):
                    n += code_length
                    continue
                else:
                    if temp > count:
                        count = temp
                        temp = 0
                    else:
                        temp = 0
            n += 1

        result.update({c: count})
    return result


def next_is_consecutive(c, dna, code_length, n):
    #  This function check whether the next sequence of DNA is still consecutive or not
    if c[0: code_length] == dna[n + code_length: n + code_length + code_length]:
        return True
    else:
        return False


def check(number, figure, s):
    #  This function check which figure's consecutive DNA match with the result of the number of consecutive DNA
    if s >= len(number):
        return True

    if int(figure[s + 1]) == number[s]:
        return check(number, figure, s + 1)
    else:
        return False


main()
