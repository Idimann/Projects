import pygame
import sys, termios, tty, os
import random

pygame.init()
pygame.font.init()

screen = pygame.display.set_mode([1500, 800])
font = pygame.font.SysFont('Consolas', 50)

running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False


