import turtle

WIDTH = 640
HEIGHT = 480

sx = 0
sy = 0
ex = WIDTH
ey = HEIGHT

wnd = turtle.Screen()
wnd.setworldcoordinates(sx, sy, ex, ey)
wnd.title("Ball Animation")

ball = turtle.Turtle()
ball.up()
ball.shape("circle")
ball.shapesize(3, 3, 8)
ball.setposition(WIDTH / 2, HEIGHT / 2)

ball.x_vel = 10
ball.y_vel = 10

ball.speed(5)

def move():
  global ball
  x, y = ball.position()
  x += ball.x_vel
  y += ball.y_vel
  if x > ex - 8 or x < sx + 8:
      ball.x_vel *= -1
  if y > ey - 8 or y < sy + 8:
      ball.y_vel *= -1
  ball.setposition(x, y)

while True:
  move()

wnd.mainloop()
