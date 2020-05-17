from cs50 import *


def main():
    s = get_int("Height: ")
    pyramid(s)


def pyramid(height):
    # check for correct usage
    if (height <= 0 or height >= 9):
        pyramid(get_int("Height?\n"))
    else:
        for i in range(height):
            temp = height - 1 - i
            
            # print spaces
            while(temp > 0):
                print(" ", end="")
                temp -= 1
            
            # print left hashes
            for j in range(i+1):
                print("#", end="")
            
            # print the space in betwen de columns
            print("  ", end="")
            
            # print the right hashes 
            for j in range(i+1):
                print("#", end="")
            
            print("")


main()
