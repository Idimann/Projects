import pygame
import sys, termios, tty, os
import random

print("The game of life!")

print("What game speed?")
gameSpeed = int(input())

print("What size?")
size = int(input())

pygame.init()

screen = pygame.display.set_mode([size * 25, size * 25])

field = [[]]

running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    newField = field

    for i in range(size):
        for j in range(size):
            neighbours = 0
            for k in range(max(j - 1, 0), min(j + 1, size - 1)):
                for m in range(max(j - 1, 0), min(j + 1, size - 1)):
                    if field[k][m]:
                        neighbours += 1
            newField[i][j] = ((neighbours == 2 or neighbours == 3) and field[i][j]) or (neighbours == 3 and not field[i][j])

    field = newField

    screen.fill((10, 10, 10))

    for i in range(size):
        for j in range(size):
            if field[i][j]:
                pygame.draw.rect(screen, (220, 220, 220), pygame.Rect(i * 25, j * 25, 25, 25))
