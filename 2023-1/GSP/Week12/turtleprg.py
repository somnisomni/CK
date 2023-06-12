import turtle
import random
import time

RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
YELLOW = (255, 255, 0)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

turtle.colormode(255)
wnd = turtle.Screen()
wnd.bgcolor(BLUE)

player = turtle.Turtle()
player.shape("circle")
player.shapesize(10)

while True:
  player.fillcolor(random.choice([RED, GREEN, BLUE, YELLOW, WHITE, BLACK]))
  time.sleep(0.1)
