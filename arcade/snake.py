import pygame
import sys, termios, tty, os
import random

print("The best boa constrictor!")

print("Input your name: ")

user = input()

print("What game speed?")
gameSpeed = int(input())

print("What mode? [A]i or [P]layer")
mode = input()

pygame.init()
pygame.font.init()

screen = pygame.display.set_mode([1000, 1000])
font = pygame.font.SysFont('Consolas', 50)

onCycle = False


def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)

    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch


def genApplePos(prevX, prevY, snakeX, snakeY, snakeLength):
    choosing = [[]]
    for i in range(40):
        for j in range(40):
            choosing.append([i * 25, j * 25])

    for i in range(snakeLength):
        if [snakeX[i], snakeY[i]] in choosing:
            choosing.remove([snakeX[i], snakeY[i]])

    return random.choice(choosing)


def genMove(posX, posY, appleX, appleY, snakeLength, prevDirection):
    global onCycle

    if posX[0] == 0:
        onCycle = False

    if not onCycle:
        if posY[0] > 0 and posX[0] == 0:
            return 0
        elif posX[0] < 975:
            return 1
        else:
            onCycle = True

    canSkip = posY[0] != 975 and prevDirection != 0 and not (appleX < posX[0] and appleY == posY[0])

    if posX[0] == 975 and posY[0] == 0:
        canSkip = False

    canSkipCheck = posX[0] == 975

    move3 = False

    for i in range(snakeLength):
        if posX[0] < posX[i] and posY[0] == posY[i]:
            move3 = True
            if posX[0] == 25:
                canSkipCheck = True
            break

    canSkip = canSkip and canSkipCheck

    if posY[0] == 0 or canSkip:
        return 2

    if (appleX < posX[0] and appleY == posY[0]) or (posX[0] > 25 and move3) or posX[0] == 975 or posY[0] == 975:
        return 3
    else:
        return 1

running = True

appleX = 475
appleY = 800

snakeX = [475, 475, 475, 475, 475]
snakeY = [500, 475, 450, 425, 400]
snakeLength = 5

moveTimer = 0
moveDirection = -1

gotPoint = False

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN and (mode == "P" or mode == "p"):
            if (event.key == pygame.K_DOWN or event.key == pygame.K_s) and moveDirection != 0:
                moveDirection = 2
            elif (event.key == pygame.K_UP or event.key == pygame.K_w) and moveDirection != 2:
                moveDirection = 0
            elif (event.key == pygame.K_RIGHT or event.key == pygame.K_d) and moveDirection != 3:
                moveDirection = 1
            elif (event.key == pygame.K_LEFT or event.key == pygame.K_a) and moveDirection != 1:
                moveDirection = 3


    screen.fill((10, 10, 10))

    if False:
        for i in range(40):
            for j in range(40):
                if (i % 2 == 0) == (j % 2 != 0):
                    pygame.draw.rect(screen, (150, 150, 150), pygame.Rect(i * 25, j * 25, 25, 25))

    for i in range(snakeLength):
        pygame.draw.rect(screen, (0, 220, 0), pygame.Rect(snakeX[i], snakeY[i], 25, 25))

    pygame.draw.rect(screen, (220, 0, 0), pygame.Rect(appleX, appleY, 25, 25))

    pygame.draw.rect(screen, (220, 0, 0), pygame.Rect(appleX, appleY, 25, 25))

    surface = font.render(str(snakeLength - 5), True, (255, 255, 255))

    screen.blit(surface, (450, 50))

    pygame.display.flip()

    if moveTimer >= gameSpeed:

        if mode == "a" or mode == "A":
            moveDirection = genMove(snakeX, snakeY, appleX, appleY,  snakeLength, moveDirection)

        if gotPoint:
            for i in range(snakeLength):
                snakeX[-i + 1] = snakeX[-i]
                snakeY[-i + 1] = snakeY[-i]

            if moveDirection == 2:
                snakeY[0] = snakeY[1] + 25
                snakeX[0] = snakeX[1]
            elif moveDirection == 0:
                snakeY[0] = snakeY[1] - 25
                snakeX[0] = snakeX[1]
            elif moveDirection == 1:
                snakeY[0] = snakeY[1]
                snakeX[0] = snakeX[1] + 25
            elif moveDirection == 3:
                snakeY[0] = snakeY[1]
                snakeX[0] = snakeX[1] - 25

            lastX = snakeX[-1]
            lastY = snakeY[-1]

            snakeX.append(lastX)
            snakeY.append(lastY)
            snakeLength += 1

            gotPoint = False
        else:
            for i in range(snakeLength):
                snakeX[-i + 1] = snakeX[-i]
                snakeY[-i + 1] = snakeY[-i]

            if moveDirection == 2:
                snakeY[0] = snakeY[1] + 25
                snakeX[0] = snakeX[1]
            elif moveDirection == 0:
                snakeY[0] = snakeY[1] - 25
                snakeX[0] = snakeX[1]
            elif moveDirection == 1:
                snakeY[0] = snakeY[1]
                snakeX[0] = snakeX[1] + 25
            elif moveDirection == 3:
                snakeY[0] = snakeY[1]
                snakeX[0] = snakeX[1] - 25

        if appleX == snakeX[0] and appleY == snakeY[0]:
            applePos = genApplePos(appleX, appleY, snakeX, snakeY, snakeLength)
            appleX = applePos[0]
            appleY = applePos[1]
            gotPoint = True

        if snakeX[0] >= 1000 or snakeX[0] < 0:
            appleX = 475
            appleY = 800

            snakeX = [475, 475, 475, 475, 475]
            snakeY = [500, 475, 450, 425, 400]
            snakeLength = 5

            moveTimer = 0
            moveDirection = -1

            gotPoint = False
        elif snakeY[0] >= 1000 or snakeY[0] < 0:
            appleX = 475
            appleY = 800

            snakeX = [475, 475, 475, 475, 475]
            snakeY = [500, 475, 450, 425, 400]
            snakeLength = 5

            moveTimer = 0
            moveDirection = -1

            gotPoint = False

        for i in range(snakeLength):
            if i != 0 and snakeX[i] == snakeX[0] and snakeY[i] == snakeY[0]:
                appleX = 475
                appleY = 800

                snakeX = [475, 475, 475, 475, 475]
                snakeY = [500, 475, 450, 425, 400]
                snakeLength = 5

                moveTimer = 0
                moveDirection = -1

                gotPoint = False
                break

        moveTimer = 0

    moveTimer += 1
