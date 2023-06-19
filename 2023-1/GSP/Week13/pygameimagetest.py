import pygame
import os

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
img = pygame.image.load("{}/image.png".format(current_path)).convert()
img_rect = img.get_rect()

playing = True
moving = False
while playing:
  fps_clock.tick(FPS)

  for event in pygame.event.get():
      if event.type == pygame.QUIT:
          playing = False
      elif event.type == pygame.MOUSEBUTTONDOWN:
        if img_rect.collidepoint(event.pos):
          moving = True
      elif event.type == pygame.MOUSEBUTTONUP:
        moving = False
      elif event.type == pygame.MOUSEMOTION and moving:
        img_rect.move_ip(event.rel)

  screen.fill(BLUE)

  screen.blit(img, img_rect)

  pygame.display.update()

pygame.quit()
