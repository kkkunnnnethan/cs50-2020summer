from cs50 import SQL
import sys
import csv


def main():

    # avoid invalid input
    if len(sys.argv) != 2:
        print("Invalid input")
        return exit(1)

    filename = sys.argv[1]

    # set up database connection
    db = SQL("sqlite:///students.db")

    with open(filename, "r") as data:
        reader = csv.DictReader(data)
        count = 0

        for row in reader:
            name = row["name"].split(" ")
            count += 1

            if len(name) == 2:
                id = count
                first = name[0]
                middle = None
                last = name[1]
                house = row["house"]
                birth = row["birth"]

            elif len(name) == 3:
                id = count
                first = name[0]
                middle = name[1]
                last = name[2]
                house = row["house"]
                birth = row["birth"]

            else:
                print("Insertion failed")
                return exit(2)

            # execute SQL queries
            db.execute("INSERT INTO students(id, first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?, ?)",
                       id, first, middle, last, house, birth)


main()
