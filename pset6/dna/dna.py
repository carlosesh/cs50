from sys import argv, exit
from cs50 import *
import csv
import re


def main():
    checkUsage()
    print(dna(argv[1], argv[2]))


def checkUsage():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)


def dna(database, sequence):

    # dictionary which will hold the colums of the database
    nucleotideDict = addKeysToDictionary(database)

    # remove the name key as it's not needed
    nucleotideDict.pop('name')

    """
    populate nucleotideDict according to the algorithm to 
    determine the sequence of nucleotide
    """
    nucleotideDict = populateDictAlgo(sequence, nucleotideDict)

    # get the DNA Match
    return getDnaMatch(database, nucleotideDict)


def getMaxSequenceValue(nucleotide, sequenceStr):
    """
    (?:TCTG)+ -> Non-capturing group + Quantifier — Matches between
    one and unlimited times, as many times as possible,
    giving back as needed (greedy) TCTG matches the characters
    TCTG literally (case sensitive)
    """
    listOfSeqOfNucleotides = re.compile(f'(?:{nucleotide})+').findall(sequenceStr)

    return 0 if len(listOfSeqOfNucleotides) == 0 else round((len(max(listOfSeqOfNucleotides))/len(nucleotide)))


def addKeysToDictionary(database):
    tempDictionary = {}
    
    # add the colums as keys from the database
    with open(database, 'r') as file:
        dbReader = csv.DictReader(file)
        for i in dbReader:
            tempDictionary = i.fromkeys(i, 0)

    return tempDictionary


def populateDictAlgo(sequence, nucleotideDict):

    tempNucleotideDict = nucleotideDict

    with open(sequence, 'r') as file:
        seqReader = csv.reader(file)

        # iterate through the sequence(s) from the csv stored in seqReader
        for sequence in seqReader:
            # create a temp variable to extract the sequence into an string format
            sequenceStr = ''.join(sequence)

            """
            for each nucleotide in nucleotideDict assing the max sequence value of the
            longest run of consecutive repeats in the sequenceStr (DNA sequence)
            """
            for nucleotide in tempNucleotideDict:
                tempNucleotideDict[nucleotide] = getMaxSequenceValue(nucleotide, sequenceStr)

    return tempNucleotideDict


def getDnaMatch(database, nucleotideDict):
    
    # return the if the ther is a match
    with open(database, 'r') as file:
        dbReader = csv.DictReader(file)
        for row in dbReader:
            counter = 0
            for key in nucleotideDict:
                if(int(row[key]) == nucleotideDict[key]):
                    counter += 1
                if(counter == len(nucleotideDict)):
                    return row["name"]

    return "No Match"


main()