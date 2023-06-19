import pygame
import os
import random

SCREEN_GEOMETRY = (640, 480)
FPS = 60

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0 , 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)

pygame.init()
screen = pygame.display.set_mode(SCREEN_GEOMETRY)
pygame.display.set_caption("Pygame Test")

fps_clock = pygame.time.Clock()

current_path = os.path.dirname(__file__)
dice_img = pygame.image.load("{}/dice.png".format(current_path))
dice_width = dice_img.get_width() // 3
dice_height = dice_img.get_height() // 2
dice_surfaces = {}
for i in range(2):
  for j in range(3):
    dice_surfaces[(i * 3) + (j + 1)] = dice_img.subsurface(j * dice_width, i * dice_height, dice_width, dice_height)
dice_xy = (SCREEN_GEOMETRY[0] // 2, SCREEN_GEOMETRY[1] // 2)
dice_rect = pygame.Rect(dice_xy[0] - dice_width // 2, dice_xy[1] - dice_height // 2, dice_width, dice_height)
dice_current = random.randint(1, 6)

playing = True
stop = True
while playing:
  fps_clock.tick(FPS)

  for event in pygame.event.get():
    if event.type == pygame.QUIT:
        playing = False
    if event.type == pygame.MOUSEBUTTONDOWN:
      if dice_rect.collidepoint(event.pos):
        stop = not stop

  screen.fill(WHITE)

  if stop: dice_current = random.randint(1, 6)
  screen.blit(dice_surfaces[dice_current], dice_rect)

  pygame.display.update()

pygame.quit()
