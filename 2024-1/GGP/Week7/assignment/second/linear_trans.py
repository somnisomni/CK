import pygame
import numpy as np

class Point:
  def __init__(self, x, y):
    self.x = x
    self.y = y

  def nparray(self):
    return np.array([self.x, self.y])

SCREEN_WIDTH = 1280
SCREEN_HEIGHT = 720
CENTER_POINT = Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)
GRID_STEP = 20
BGCOLOR = (245, 245, 245)
LINECOLOR = (200, 200, 200)

def convertAxis(points: tuple[int, int]):
  return [(CENTER_POINT.x + point[0], CENTER_POINT.y - point[1]) for point in points]

pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Rect")
running = True

while running:
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      running = False

  screen.fill(BGCOLOR)

  for y in range(0, SCREEN_HEIGHT, GRID_STEP):
    width = 3 if y == CENTER_POINT.y else 1
    pygame.draw.line(screen, LINECOLOR, (0, y), (SCREEN_WIDTH, y), width)

  for x in range(0, SCREEN_WIDTH, GRID_STEP):
    width = 3 if x == CENTER_POINT.x else 1
    pygame.draw.line(screen, LINECOLOR, (x, 0), (x, SCREEN_HEIGHT), width)

  # === MAIN === #
  RECT_WIDTH = 100
  RECT_HEIGHT = 100
  ORIGIN = Point(0, 0)
  RECTCOLOR = (255, 0, 0)
  TRANSLATE_AMOUNT = 0.5

  whVec = np.array([RECT_WIDTH,
                    RECT_HEIGHT])
  transVec = np.array([[1, TRANSLATE_AMOUNT],
                       [0, 1]])

  resultVec = np.matmul(transVec, whVec) + ORIGIN.nparray()

  pygame.draw.polygon(screen, RECTCOLOR, convertAxis([
    (ORIGIN.x,     ORIGIN.y),
    ((resultVec[0] - RECT_WIDTH), resultVec[1]),
    (resultVec[0], resultVec[1]),
    (whVec[0] + ORIGIN.x,     (resultVec[1] - RECT_HEIGHT))
  ]))
  # === === #

  pygame.display.flip()

pygame.quit()
