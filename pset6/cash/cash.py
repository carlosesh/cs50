from cs50 import *
import math


def main():
    print(getChange(get_float("Change owed: ")))


def getChange(n):
    if(n <= 0):
        return getChange(get_float("Change owed: "))
    else:
        coins = [25, 10, 5, 1]
        cents = n*100
        result = 0

        for i in range(len(coins)):
            temp = math.floor(cents / coins[i])
            result += temp
            cents -= (temp * coins[i])

        return result


main()