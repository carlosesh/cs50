from cs50 import *


def main():
    s = get_int("Height: ")
    rightAlinedPyramid(s)


def rightAlinedPyramid(height):
    # check for correct usage
    if (height <= 0 or height >= 9):
        rightAlinedPyramid(get_int("Height?\n"))
    else:
        for i in range(height):
            j = i
            temp = height - 1 - i
            while(temp > 0):
                print(" ", end="")
                temp -= 1
            for j in range(i+1):
                print("#", end="")
            print("")


main()
