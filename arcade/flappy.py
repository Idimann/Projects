import pygame
import sys, termios, tty, os
import random
import time

print("[A]i or [P]layer?")
mode = input()

allowTrolling = input("Trolling y/n: ")

# Scoreboard Shit
scoreboard = open("Scoreboard.txt", "a")

if not os.path.exists("Scoreboard.txt"):
    scoreboard = open("Scoreboard.txt", "w+")

user = "Skynet"

if mode == 'P' or mode == 'p':
    user = input("Provide your username: ")

pygame.init()
pygame.font.init()

screen = pygame.display.set_mode([1500, 800])
font = pygame.font.SysFont('Consolas', 50)

gravity = 0.15
speed = 0.5

score = 0
scoreIncreased = False

running = True

position = 400.0
velocity = 0.0

printing = True

troll = False

scrollProgress = 0

pipes = [[1600, 350, False], [2000, 400, False], [2400, 200, False], [2800, 530, False], [3200, 101, False]]


def scoreboardPrinting():
    global screen
    global font

    players = [["", 0] for i in range(50)]

    with open("Scoreboard.txt") as file:
        for line in file:
            if '=' not in line.rstrip():
                continue

            name = line.rstrip().split('=')[0]
            score = int(line.rstrip().split('=')[1])

            for i in range(50):
                if score > players[i][1]:

                    for j in reversed(range(i, 50)):
                        if j != 49:
                            players[j + 1] = players[j]

                    players[i] = [name, score]
                    break

    for i in range(scrollProgress, scrollProgress + 10):
        surface = font.render(str(i + 1) + ".    " + players[i][0], True, (255, 255, 255))

        if i > 8:
            surface = font.render(str(i + 1) + ".   " + players[i][0], True, (255, 255, 255))

        screen.blit(surface, (50, 25 + (i - scrollProgress) * 75))

        surface = font.render("|    " + str(players[i][1]), True, (255, 255, 255))
        screen.blit(surface, (1000, 25 + (i - scrollProgress) * 75))


def scoreboardShit():
    global score
    global user
    global scoreboard

    if score == 0:
        return

    with open("Scoreboard.txt") as file:
        for line in file:
            if '=' not in line.rstrip():
                continue

            if line.rstrip().split('=')[0] == user and int(line.rstrip().split('=')[1]) >= score:
                return

    scoreboard.write('\n' + user + '=' + str(score))

    scoreboard.close()
    scoreboard = open("Scoreboard.txt", "a")


def ai():
    global pipes
    global position

    last = 4000
    lastY = 0

    for pipe in pipes:
        if pipe[0] < last and pipe[0] > 100:
            last = pipe[0]
            lastY = pipe[1]

    return position > lastY + 265


while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif not printing and (mode == 'P' or mode == 'p') and event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                velocity = -20
        elif printing and event.type == pygame.KEYDOWN:
            if event.key == pygame.K_RETURN:
                printing = False
            elif event.key == pygame.K_DOWN:
                scrollProgress += 1
            elif event.key == pygame.K_UP and scrollProgress > 0:
                scrollProgress -= 1

    if not printing and (mode == 'A' or mode == 'a') and ai():
        velocity = -20

    screen.fill((10, 10, 10))
    if printing:
        scoreboardPrinting()
        pygame.display.flip()
    else:
        pygame.draw.rect(screen, (220, 220, 0), pygame.Rect(250, position, 35, 35))

        if (allowTrolling == 'y' or allowTrolling == 'Y') and score % 10 == 0 and not score == 0 and scoreIncreased:
            troll = not troll
            scoreIncreased = False

        for pipe in pipes:
            pygame.draw.rect(screen, (0, 240, 0), pygame.Rect(pipe[0], 0, 150, pipe[1]))
            pygame.draw.rect(screen, (0, 240, 0), pygame.Rect(pipe[0], pipe[1] + 300, 150, 800))

            if position < 0 or position > 800 or (pipe[0] < 250 and pipe[0] > 100 and not troll == (position < pipe[1] or position > pipe[1] + 300)):
                pipes = [[1600, 350, False], [2000, 400, False], [2400, 200, False], [2800, 530, False], [3200, 101, False]]
                position = 400
                velocity = 0
                speed = 0.5

                scoreboardShit()
                printing = True

                score = 0

            pipe[0] -= speed

            if pipe[0] <= -200:
                pipe[1] = random.randrange(0, 500)
                pipe[0] = 1800
                pipe[2] = False
                if score < 50:
                    speed += 0.01

            if pipe[0] <= 100 and not pipe[2]:
                score += 1
                scoreIncreased = True
                pipe[2] = True

        surface = font.render(str(score), True, (255, 255, 255))

        screen.blit(surface, (700, 50))

        pygame.display.flip()

        position += velocity / 10
        velocity += gravity
