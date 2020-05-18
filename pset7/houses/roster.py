from sys import argv, exit
import cs50
import csv
import re

db = cs50.SQL("sqlite:///students.db")


def main():
    checkUsage()
    roster(argv[1])


def checkUsage():
    # check if there are not exactly 2 arguments then exit the program
    if len(argv) != 2:
        print("Usage: python import.py data.csv")
        exit(1)


def roster(house):
    # get the ouput of execute in a dictionary
    query = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? order by last, first asc;", house)
    
    # iterate through the query and return the output as needed
    for row in query:
        # if the middle name is NUll then ommit it
        if(row['middle'] == None):
            print("{} {}, born {}".format(row['first'], row['last'], row['birth']))
        else:
            print("{} {} {}, born {}".format(row['first'], row['middle'], row['last'], row['birth']))
            

main()