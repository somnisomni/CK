import pygame
import numpy as np

class Point:
  def __init__(self, x, y):
    self.x = x
    self.y = y

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

  # === AXIS === #
  for x in range(int(CENTER_POINT.x), SCREEN_WIDTH, GRID_STEP):
    pygame.draw.line(screen, LINECOLOR, (x, 0), (x, SCREEN_HEIGHT), 1)

  for x in range(int(CENTER_POINT.x), 0, -GRID_STEP):
    pygame.draw.line(screen, LINECOLOR, (x, 0), (x, SCREEN_HEIGHT), 1)

  for y in range(int(CENTER_POINT.y), SCREEN_HEIGHT, GRID_STEP):
    pygame.draw.line(screen, LINECOLOR, (0, y), (SCREEN_WIDTH, y), 1)

  for y in range(int(CENTER_POINT.y), 0, -GRID_STEP):
    pygame.draw.line(screen, LINECOLOR, (0, y), (SCREEN_WIDTH, y), 1)

  pygame.draw.line(screen, LINECOLOR, (0, CENTER_POINT.y), (SCREEN_WIDTH, CENTER_POINT.y), 3)
  pygame.draw.line(screen, LINECOLOR, (CENTER_POINT.x, 0), (CENTER_POINT.x, SCREEN_HEIGHT), 3)
  # === === #

  # === MAIN === #
  RECT_WIDTH = 100
  RECT_HEIGHT = 100
  ORIGIN = Point(0, 0)
  ORIGIN_XINV = Point(RECT_WIDTH, 0)
  RECTCOLOR = (255, 0, 0)

  SIZE_MUL = 2
  ROT_DEGREES = 45
  TRANSLATE_X = 50
  TRANSLATE_Y = 50

  whM = np.array([RECT_WIDTH,
                  RECT_HEIGHT,
                  1])
  mulM = np.array([[SIZE_MUL, 0, 0],
                   [0, SIZE_MUL, 0],
                   [0, 0, 1]])
  rotM = np.array([
    [np.cos(np.radians(ROT_DEGREES)), -np.sin(np.radians(ROT_DEGREES)), 0],
    [np.sin(np.radians(ROT_DEGREES)),  np.cos(np.radians(ROT_DEGREES)), 0],
    [0, 0, 1]
  ])
  transM = np.array([[1, 0, ORIGIN.x + TRANSLATE_X],
                     [0, 1, ORIGIN.y + TRANSLATE_Y],
                     [0, 0, 1]])

  resultM = np.matmul(transM, rotM)
  resultM = np.matmul(resultM, mulM)
  resultM = np.matmul(resultM, whM)

  P1 = (transM[0, 2], transM[1, 2])
  P2 = ((rotM[0, 0] * RECT_WIDTH * SIZE_MUL) + transM[0, 2], (rotM[1, 0] * RECT_HEIGHT * SIZE_MUL) + transM[1, 2])
  P3 = (resultM[0], resultM[1])
  P4 = ((rotM[0, 1] * RECT_WIDTH * SIZE_MUL) + transM[0, 2], (rotM[1, 1] * RECT_HEIGHT * SIZE_MUL) + transM[1, 2])

  pygame.draw.polygon(screen, RECTCOLOR, convertAxis([P1, P2, P3, P4]))
  # === === #

  pygame.display.flip()

pygame.quit()
