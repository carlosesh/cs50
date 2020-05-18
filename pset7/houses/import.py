from sys import argv, exit
import cs50
import csv
import re

db = cs50.SQL("sqlite:///students.db")


def main():
    checkUsage()
    importData(argv[1])


def checkUsage():
    # check if there are not exactly 2 arguments then exit the program
    if len(argv) != 2:
        print("Usage: python import.py data.csv")
        exit(1)


def importData(data):
    # get the data from the csv, then iterate through it an call importRowToDb on each row
    with open(data, 'r') as file:
        data = csv.DictReader(file)
        for row in data:
            importRowToDb(row)


def importRowToDb(row):
    # get all the values required from the row
    name = row['name'].split()
    house = row['house']
    birth = row['birth']

    # check if the name has a middle name, if 2 means there is a middle name else no middle name
    if(len(name) == 3):
        # use the split values from the name array and assign them accordingly
        first = name[0]
        middle = name[1]
        last = name[2]

        # execute insert statement
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   first, middle, last, house, birth)
    else:
        first = name[0]
        last = name[1]

        # execute insert statement
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   first, None, last, house, birth)


main()