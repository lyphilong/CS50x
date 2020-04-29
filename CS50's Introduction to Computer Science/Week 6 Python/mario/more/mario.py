from cs50 import get_int

height = get_int("Height: ")


while(int(height) <= 0 or int(height) == 9):
    height = input("Height: ")

for i in range(1, int(height) + 1):
    print(" "*(int(height) - i) + "#" * i + "  " + "#"*i, end="\n")