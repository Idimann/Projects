import pygame
import sys, termios, tty, os, time


class centipede:
    x = []
    y = []

    def __init__(self, x, y):
        self.x = x
        self.y = y


print("I hate insects")

print("Input the game speed: ", end = "")

gameSpeed = int(input())

print()

pygame.init()
pygame.font.init()

screen = pygame.display.set_mode([500, 1000])
font = pygame.font.SysFont('Consolas', 50)

running = True

playerPos = 240

gameCounter = 0

centipides = []

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill((0, 0, 0))
    pygame.draw.polygon(screen, (255, 255, 0), ((playerPos - 10, 975), (playerPos, 950), (playerPos + 10, 975)))
    pygame.display.flip()

    if gameSpeed != gameCounter:
        gameCounter += 1
        continue

    gameCounter = 0

    keys = pygame.key.get_pressed()

    if keys[pygame.K_LEFT]:
        playerPos -= 5

    if keys[pygame.K_RIGHT]:
        playerPos += 5


