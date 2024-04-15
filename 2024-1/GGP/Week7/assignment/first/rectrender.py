import pygame

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
RECTCOLOR = (255, 0, 0)

RECTPOINTS = [
    (0, 0),
    (0, 100),
    (100, 100),
    (100, 0)
]

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

  pygame.draw.polygon(screen, RECTCOLOR, convertAxis(RECTPOINTS))
  # pygame.draw.polygon(screen, RECTCOLOR, convertAxis(RECTPOINTS), 1)

  pygame.display.flip()

pygame.quit()
