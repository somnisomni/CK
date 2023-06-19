import pygame

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

x = 320
y = 240
accel = 0
speed = 5
circle = pygame.Rect(x, y, 40, 40)
circle_vel = pygame.Vector2()

playing = True
moving = False
while playing:
  fps_clock.tick(FPS)

  for event in pygame.event.get():
      if event.type == pygame.QUIT:
          playing = False
      elif event.type == pygame.MOUSEBUTTONDOWN:
        if circle.collidepoint(event.pos):
          moving = True
      elif event.type == pygame.MOUSEBUTTONUP:
        moving = False
      elif event.type == pygame.MOUSEMOTION and moving:
        circle.move_ip(event.rel)

  key_event = pygame.key.get_pressed()
  if key_event[pygame.K_LEFT] or key_event[pygame.K_RIGHT] or key_event[pygame.K_UP] or key_event[pygame.K_DOWN]:
    accel += 0.025 if accel < 1 else 0
  else:
    circle_vel.xy = (0, 0)
    accel = 0

  if key_event[pygame.K_LEFT]:
    circle_vel.x = -speed * accel if x > 0 else 0
  if key_event[pygame.K_RIGHT]:
    circle_vel.x = speed * accel  if x < SCREEN_GEOMETRY[0] else 0
  if key_event[pygame.K_UP]:
    circle_vel.y = -speed * accel  if y > 0 else 0
  if key_event[pygame.K_DOWN]:
    circle_vel.y = speed * accel  if y < SCREEN_GEOMETRY[1] else 0

  # mouse_event = pygame.mouse.get_pos()
  # x = mouse_event[0]
  # y = mouse_event[1]

  screen.fill(BLUE)

  # pygame.draw.circle(screen, RED, (x, y), 10)
  circle.move_ip(circle_vel)
  pygame.draw.ellipse(screen, RED, circle)


  pygame.display.update()



pygame.quit()
