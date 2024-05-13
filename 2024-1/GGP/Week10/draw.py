from typing import List, Tuple
import pygame

SCREEN_WIDTH = 1280
SCREEN_HEIGHT = 720
BGCOLOR = (255, 255, 255)

def drawLine(screen: pygame.Surface, p1: Tuple[int, int], p2: Tuple[int, int], color: Tuple[int, int, int]):
  pLeft, pRight = (p1, p2) if p1[0] < p2[0] else (p2, p1)

  dx = pRight[0] - pLeft[0]
  dy = pRight[1] - pLeft[1]
  predict = (-2 * dy) + dx

  y = pLeft[1]
  for x in range(pLeft[0], pRight[0] + 1):
    screen.set_at((x, y), color)

    if predict >= 0:
      predict += -2 * dy
    else:
      y += 1
      predict += (-2 * dy) + (2 * dx)

def drawTriangle(screen: pygame.Surface, vertices: List[Tuple[int, int]], color: Tuple[int, int, int]):
  # incomplete implementation
  for i in range(3):
    drawLine(screen, vertices[i], vertices[(i + 1) % 3], color)

pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Draw Line")
running = True

while running:
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      running = False

  screen.fill(BGCOLOR)

  drawLine(screen, (25, 50), (300, 200), (0, 0, 0))
  drawLine(screen, (310, 210), (35, 60), (0, 128, 0))

  drawTriangle(screen, [(300, 300), (100, 400), (500, 500)], (255, 0, 0))

  pygame.display.flip()

pygame.quit()
