from cs50 import get_int


def main():

    # Get input only between 1 - 8
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break

    recursiveHash(height, 0)


def recursiveHash(height, spaces):

    # Base case
    if height <= 0:
        return

    # Print pyramid of height - 1
    recursiveHash(height - 1, spaces + 1)

    # Print spaces
    for i in range(spaces):
        print(" ", end="")

    # Print first hashes
    for i in range(height):
        print("#", end="")

    # Print middle spaces
    print("  ", end="")

    # Print second hashes
    for i in range(height):
        print("#", end="")

    # Move to new line
    print("")


main()
