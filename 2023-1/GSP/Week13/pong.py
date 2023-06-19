# 강의 중에 맘대로 짜본 퐁 게임

import pygame

SCREEN_GEOMETRY = (640, 480)
FPS = 120

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

pygame.init()
screen = pygame.display.set_mode(SCREEN_GEOMETRY)
pygame.display.set_caption("Pong")

fps_clock = pygame.time.Clock()

ball = pygame.Rect(SCREEN_GEOMETRY[0] // 2, SCREEN_GEOMETRY[1] // 2, 10, 10)
ball_velocity = pygame.Vector2(2, 2)
player1 = pygame.Rect(10, SCREEN_GEOMETRY[1] // 2, 10, 100)
player2 = pygame.Rect(SCREEN_GEOMETRY[0] - 20, SCREEN_GEOMETRY[1] // 2, 10, 100)

total_pongs = 0

playing = True
while playing:
  fps_clock.tick(FPS)

  for event in pygame.event.get():
      if event.type == pygame.QUIT:
          playing = False

  key_event = pygame.key.get_pressed()
  if key_event[pygame.K_w] and player1.y > 0:
    player1.move_ip(0, -3)
  if key_event[pygame.K_s] and player1.y < SCREEN_GEOMETRY[1] - player1.height:
    player1.move_ip(0, 3)
  if key_event[pygame.K_UP] and player2.y > 0:
    player2.move_ip(0, -3)
  if key_event[pygame.K_DOWN] and player2.y < SCREEN_GEOMETRY[1] - player2.height:
    player2.move_ip(0, 3)

  if player1.colliderect(ball) or player2.colliderect(ball):
    # Workaround for a bug where the ball would get stuck inside the player paddle
    if player1.colliderect(ball):
      ball.left = player1.right
    else:
      ball.right = player2.left

    ball_velocity.xy = (ball_velocity.x * 1.025, ball_velocity.y * 1.025)
    ball_velocity.x *= -1
    total_pongs += 1

  if not (ball.y > 0 and ball.y < SCREEN_GEOMETRY[1]):
    ball_velocity.y *= -1

  if ball.x < 0 or ball.x > SCREEN_GEOMETRY[0]:
    print("RESET")
    ball.x = SCREEN_GEOMETRY[0] // 2
    ball.y = SCREEN_GEOMETRY[1] // 2
    ball_velocity.xy = (2, 2)

  screen.fill(BLACK)
  ball.move_ip(ball_velocity)
  pygame.draw.rect(screen, WHITE, player1)
  pygame.draw.rect(screen, WHITE, player2)
  pygame.draw.ellipse(screen, WHITE, ball)

  # draw pong count text
  font = pygame.font.SysFont("Consolas", 40)
  text = font.render(str(total_pongs), True, WHITE)
  screen.blit(text, (SCREEN_GEOMETRY[0] // 2, 0))

  pygame.display.update()

pygame.quit()
