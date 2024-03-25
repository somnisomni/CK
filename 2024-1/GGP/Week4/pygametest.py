import pygame
pygame.init()
screenWidth = 1280
screenHeight = 720
BACKGROUND_COLR = (217,217,217)
screen = pygame.display.set_mode((screenWidth, screenHeight))
pygame.display.set_caption("Graphics Programming")
running = True

while running:
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      running = False
  screen.fill(BACKGROUND_COLR)
  pygame.display.flip()
pygame.quit()
