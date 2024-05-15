from cs50 import get_string
import sys


def main():
    input = get_string("Number: ")

    print(len(input))

    if len(input) != 13 and len(input) != 15 and len(input) != 16:
        print("INVALID")
        return

    if input.isnumeric() == False:
        print("INVALID")
        return

    if is_master_card(input) or is_american(input) or is_visa(input):
        if checksum(input):
            print(what_type(input))
        else:
            print("INVALID")

    else:
        print("INVALID")
        return


def what_type(card):
    if is_master_card(card):
        return "MASTERCARD"
    if is_visa(card):
        return "VISA"
    if is_american(card):
        return "AMEX"

    return "-1"


def checksum(number):
    pos1 = len(number)-2
    pos2 = len(number)-1
    checksum = 0
    while pos1 >= 0:
        num = int(number[pos1]) * 2
        print(num)
        if num > 9:
            newNum = num % 10
            checksum += newNum
            num = int(num / 10)
            checksum += num
        else:
            checksum += num
        pos1 -= 2

    while pos2 >= 0:
        num = int(number[pos2])
        checksum += num
        pos2 -= 2

    if checksum % 10 == 0:
        return True
    else:
        return False


def is_master_card(number):
    startNumbers = ["51", "52", "53", "54", "55"]
    for startNumber in startNumbers:
        if number.startswith(startNumber):
            return True

    return False


def is_american(number):
    if number.startswith("34") or number.startswith("37"):
        return True

    return False


def is_visa(number):
    return number.startswith("4")


if __name__ == "__main__":
    main()
