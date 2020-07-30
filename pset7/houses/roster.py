from cs50 import SQL
import sys
import csv


def main():

    # avoid invalid input
    if len(sys.argv) != 2:
        print("Invalid input")
        return exit(1)

    # avoid wrong house
    if sys.argv[1] != "Gryffindor" and \
            sys.argv[1] != "Hufflepuff" and \
            sys.argv[1] != "Ravenclaw" and \
            sys.argv[1] != "Slytherin":
        print("This house does not exist")
        return exit(1)

    goalhouse = sys.argv[1]

    # set up database connection
    db = SQL("sqlite:///students.db")

    # execute SQL queries
    students = db.execute("SELECT * FROM students ORDER BY last, first")

    for person in students:
        if person.get("house") == goalhouse:
            if person.get("middle") is None:
                print(person.get("first") + " " + person.get("last") + ", born " + str(person.get("birth")))
            else:
                print(person.get("first") + " " + person.get("middle") + " " + person.get("last") + ", born " + str(person.get("birth")))


main()
