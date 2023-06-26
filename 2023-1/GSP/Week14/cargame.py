import pygame
import os
import random
import time

CURRENT_DIRECTORY = os.path.dirname(__file__)
SCREEN_WIDTH = 400
SCREEN_HEIGHT = 600
FPS = 60

class Player(pygame.sprite.Sprite):
  def __init__(self):
    super().__init__()
    self.image = pygame.image.load(os.path.join(CURRENT_DIRECTORY, "res/Player.png"))
    self.rect = self.image.get_rect()
    self.rect.center = (200, SCREEN_HEIGHT - 128)

  def handle_keypress(self):
    ke = pygame.key.get_pressed()
    if ke[pygame.K_LEFT] and self.rect.left > 50:
      self.rect.move_ip(-5, 0)
    elif ke[pygame.K_RIGHT] and self.rect.right < SCREEN_WIDTH - 50:
      self.rect.move_ip(5, 0)

class Enemy(pygame.sprite.Sprite):
  def __init__(self, x = 80):
    super().__init__()
    self.image = pygame.image.load(os.path.join(CURRENT_DIRECTORY, "res/Enemy.png"))
    self.rect = self.image.get_rect()
    self.rect.center = (x, -50)

  def update(self, speed = 1.0):
    self.rect.move_ip(0, 2 * speed)

    if self.rect.top > SCREEN_HEIGHT:
      self.kill()
      return True

pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Car Game")

fps_clock = pygame.time.Clock()

AUDIO_CRASH = pygame.mixer.Sound(open(os.path.join(CURRENT_DIRECTORY, "res/crash.wav")))
SPRITE_STREET = pygame.image.load(os.path.join(CURRENT_DIRECTORY, "res/Street.png"))
PLAYER = Player()
ENEMIES = pygame.sprite.Group()

pygame.mixer.init()
pygame.mixer.music.load(open(os.path.join(CURRENT_DIRECTORY, "res/background.wav")))
pygame.mixer.music.play(loops=-1)

SPEED_UP_EVENT = pygame.USEREVENT + 1
pygame.time.set_timer(SPEED_UP_EVENT, 1000)

timer_tick = 0
speed = 1.0
street_y = 0
playing = True
while playing:
  fps_clock.tick(FPS)
  timer_tick += fps_clock.get_time()

  if timer_tick >= (5000 * (random.random() + 0.5)):
    ENEMIES.add(Enemy(random.randint(80, SCREEN_WIDTH - 80)))
    timer_tick = 0

  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      playing = False
    elif event.type == SPEED_UP_EVENT:
      speed += 0.1

  if street_y >= SCREEN_HEIGHT: street_y = 0
  else: street_y += 2 * speed

  PLAYER.handle_keypress()
  for e in ENEMIES:
    if ENEMIES.update(speed): ENEMIES.remove(e)

  screen.blits([(SPRITE_STREET, (0, street_y)), (SPRITE_STREET, (0, street_y - SCREEN_HEIGHT))])
  screen.blit(PLAYER.image, PLAYER.rect)
  screen.blits([(e.image, e.rect) for e in ENEMIES])

  if pygame.sprite.spritecollideany(PLAYER, ENEMIES):
    AUDIO_CRASH.play()
    time.sleep(2)
    playing = False
    break

  pygame.display.update()

pygame.quit()
