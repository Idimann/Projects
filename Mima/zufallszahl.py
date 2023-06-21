import random


def programm(number):
    randomNumber = random.randint(0, 10)

    if number == randomNumber:
        print("Hey")
        return True
    else:
        print("Ney")
        return False


while True:
    print("Gib eine Zahl zwischen 0 und 10 ein bitte :) (exit um zu beenden)")
    zahl = input()

    if zahl == "exit" or programm(int(zahl)):
        break
