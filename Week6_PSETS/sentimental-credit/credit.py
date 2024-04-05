from cs50 import get_int
from math import floor


def main():

    # Use of get_int to reject non-numeric values
    cNum = get_int("Number: ")

    # Get length of number
    length = len(str(cNum))

    # Reject any non-valid length
    if length != 13 and length != 15 and length != 16:
        print("INVALID")
        return 1

    # Helper function for Luhn's Algorithm
    luhnCalc(cNum, length)


def luhnCalc(cNum, length):

    # Create variables
    total = 0
    sum1 = 0
    sum2 = 0

    # Placeholder for sum2 before adding
    preAddSum2 = 0

    # Create variable to work on cNum
    n = cNum

    # Iterate over number
    for i in range(floor(length / 2)):
        # Add last digit to sum1 with modulo 10
        sum1 += n % 10

        # Divide by 10 for next digit, floor to avoid floats
        n = floor(n / 10)

        # Multiply second to last digit
        preAddSum2 = (n % 10) * 2
        # Check if >= 10
        if preAddSum2 >= 10:
            # Add second digit
            sum2 += preAddSum2 % 10
            # Divide by 10 for next digit, floor to avoid floats
            preAddSum2 = floor(preAddSum2 / 10)
            # Add first digit
            sum2 += preAddSum2
        else:
            # Add second to last digit multiplied by 2
            sum2 += preAddSum2

        # Divide by 10 for next digit, floor to avoid floats
        n = floor(n / 10)

    # Add last digit for length of 13 & 15
    if length != 16:
        sum1 += n % 10

    # Total up both sums
    total += sum1 + sum2

    if total % 10 != 0:
        print("INVALID")
        return 1

    # Helper function to print card
    printCard(cNum, length)


def printCard(cNum, length):

    # Get first two digits
    firstTwoNums = int(str(cNum)[:2])

    # Switch statement to validate card
    match length:

        # VISA length
        case 13:
            # Check first digit for 4
            if floor(firstTwoNums / 10) == 4:
                print("VISA")
                return
            else:
                print("INVALID")
                return 1

        # AMEX length
        case 15:
            # Check for 34 or 37
            if firstTwoNums == 34 or firstTwoNums == 37:
                print("AMEX")
                return
            else:
                print("INVALID")
                return 1

        # VISA or MASTERCARD length
        case 16:
            # Check first digit for 4
            if floor(firstTwoNums / 10) == 4:
                print("VISA")
                return
            # Check for 51 -> 55
            elif firstTwoNums >= 51 and firstTwoNums <= 55:
                print("MASTERCARD")
                return
            else:
                print("INVALID")
                return


main()
