import pygame
import random
import os
import time

CURRENT_DIRECTORY = os.path.dirname(__file__)
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
FPS = 60

RED = (255, 0, 0)
BLUE = (0, 0, 255)
BLACK = (0, 0, 0)

pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Shooting Game")

AUDIO_BULLETFIRE = pygame.mixer.Sound(open(os.path.join(CURRENT_DIRECTORY, "res/bulletSound.wav")))
AUDIO_DESTROY = pygame.mixer.Sound(open(os.path.join(CURRENT_DIRECTORY, "res/destroy.wav")))

fps_clock = pygame.time.Clock()
SPEED = 5

class Player(pygame.sprite.Sprite):
  def __init__(self):
    super().__init__()
    self.image = pygame.image.load(os.path.join(CURRENT_DIRECTORY, "res/shootingplayer.png"))
    self.image = pygame.transform.scale(self.image, (30, 50))
    self.rect = self.image.get_rect()
    self.rect.center = (SCREEN_WIDTH // 2, SCREEN_HEIGHT - self.image.get_height() - 10)
    self.vel = pygame.Vector2(0,0)
    self.fire_press_count = -1

  def handle_keypress(self):
    kev = pygame.key.get_pressed()
    if kev[pygame.K_LEFT] and self.rect.left >= 0:
      self.vel.x = -SPEED
    elif kev[pygame.K_RIGHT] and self.rect.right <= SCREEN_WIDTH:
      self.vel.x = SPEED
    else:
      self.vel.x = 0

    if kev[pygame.K_UP] and self.rect.top >= 0:
      self.vel.y = -SPEED
    elif kev[pygame.K_DOWN] and self.rect.bottom <= SCREEN_HEIGHT:
      self.vel.y = SPEED
    else:
      self.vel.y = 0

    if kev[pygame.K_SPACE]:
      self.fire_press_count += 1

      if self.fire_press_count == 0:
        ALL_SPRITES.add(Bullet(self.rect.centerx, self.rect.top))
        AUDIO_BULLETFIRE.play()
      elif self.fire_press_count == 10:
        self.fire_press_count = -1
    else:
      self.fire_press_count = -1

  def check_collide(self):
    if pygame.sprite.spritecollideany(self, ENEMIES):
      for e in ENEMIES: e.kill()
      for sprite in ALL_SPRITES: sprite.kill()
      time.sleep(2)
      pygame.quit()

  def move(self):
    self.rect.move_ip(self.vel)

  def update(self):
    self.handle_keypress()
    self.check_collide()
    self.move()

class Enemy(pygame.sprite.Sprite):
  def __init__(self):
    super().__init__()
    self.rect = pygame.Rect(0, 0, 32, 32)
    self.image = pygame.Surface(self.rect.size, masks=pygame.SRCALPHA)
    self.rect = pygame.draw.rect(self.image, RED, self.rect)
    self.rect.center = (random.randint(10, SCREEN_WIDTH - 10), random.randint(-SCREEN_HEIGHT, -self.rect.height))
    self.speed = 5

  def reposition(self):
    x = random.randint(10, SCREEN_WIDTH-10)
    y = random.randint(-SCREEN_HEIGHT, -10)
    self.rect.center = (x, y)

  def move(self):
    self.rect.move_ip(0, self.speed)

  def update(self):
    self.move()
    if self.rect.top >= SCREEN_HEIGHT:
      self.reposition()
      self.speed += 0.1

class Bullet(pygame.sprite.Sprite):
  def __init__(self, x, y):
    super().__init__()
    self.rect = pygame.Rect(0, 0, 8, 8)
    self.image = pygame.Surface(self.rect.size, masks=pygame.SRCALPHA)
    self.rect = pygame.draw.circle(self.image, BLUE, self.rect.center, self.rect.width / 2)
    self.rect.center = (x, y)

  def check_collide(self):
    collide: Enemy = pygame.sprite.spritecollideany(self, ENEMIES)
    if collide:
      AUDIO_DESTROY.play()
      collide.reposition()
      ALL_SPRITES.remove(self)

  def move(self):
    self.rect.move_ip(0, -SPEED)

  def update(self):
    self.check_collide()
    self.move()

    if self.rect.bottom <= 0:
      ALL_SPRITES.remove(self)

PLAYER = Player()

ALL_SPRITES = pygame.sprite.Group()
ALL_SPRITES.add(PLAYER)

ENEMIES = pygame.sprite.Group()
for _ in range(10):
  e = Enemy()
  ENEMIES.add(e)
  ALL_SPRITES.add(e)

pygame.mixer.init()
pygame.mixer.music.load(os.path.join(CURRENT_DIRECTORY, "res/shootingbg.mp3"))
pygame.mixer.music.play(loops=-1)
pygame.mixer.music.set_volume(0.75)

running = True
while running:
    fps_clock.tick(FPS)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill(BLACK)
    for sp in ALL_SPRITES:
        sp.update()
        screen.blit(sp.image, sp.rect)

    pygame.display.update()

pygame.quit()
