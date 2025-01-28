import pygame

pygame.init()
pygame.font.init()

screen = pygame.display.set_mode([1000, 1000])
font = pygame.font.SysFont('Consolas', 50)

running = True

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
