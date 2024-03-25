import pygame

SCREEN_WIDTH = 1280
SCREEN_HEIGHT = 720
GRID_STEP = 10
BGCOLOR = (245, 245, 245)

pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Axis")
running = True

while running:
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      running = False

  screen.fill(BGCOLOR)

  for y in range(0, SCREEN_HEIGHT, GRID_STEP):
    width = 3 if y == SCREEN_HEIGHT / 2 else 1
    pygame.draw.line(screen, (200, 200, 200), (0, y), (SCREEN_WIDTH, y), width)

  for x in range(0, SCREEN_WIDTH, GRID_STEP):
    width = 3 if x == SCREEN_WIDTH / 2 else 1
    pygame.draw.line(screen, (200, 200, 200), (x, 0), (x, SCREEN_HEIGHT), width)

  pygame.display.flip()

pygame.quit()
