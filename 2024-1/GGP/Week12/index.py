import pygame
import numpy as np
from pygame.locals import *
from objects import *
from util import *

SCREEN_WIDTH = 1280
SCREEN_HEIGHT = 720
SCREEN_CENTER = (SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)
FPS = 60
BACKGROUND_COLOR = (255, 255, 255)

# RIGHT-HAND COORDINATE SYSTEM
camera = Camera((0, 0, 10), (0, 0, 0), 90)

cube = Cube((0, 0, 0), 100, 100, 100)

# Initialize
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
clock = pygame.time.Clock()

# Loop
running = True
while running:
  # Quit event
  for event in pygame.event.get():
    if event.type == QUIT:
      running = False

  # Clear
  screen.fill(BACKGROUND_COLOR)

  # Draw
  vertices = cube.verticesToWorldMatrix()
  for vertex in vertices:
    v = np.matmul(camera.posToViewMatrix(), vertex)
    v = pointMatrixToScreenMatrix(v, SCREEN_CENTER)
    pygame.draw.circle(screen, (0, 0, 0), screenMatrixToPoint(v), 5)

  # Flip
  pygame.display.flip()
  clock.tick(FPS)

# Quit
pygame.quit()
