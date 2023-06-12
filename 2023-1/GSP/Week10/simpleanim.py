from turtle import *
from threading import Thread
import time
import random

class NonBlockingLoop(Thread):
  _COLORS = ["red", "green", "blue", "yellow", "orange"]

  def __init__(self, turtle):
    Thread.__init__(self)
    self.turtle = turtle

  def run(self):
    while True:
      self.turtle.shape("square")
      self.turtle.color(random.choice(self._COLORS))
      time.sleep(0.5)

      self.turtle.shape("circle")
      self.turtle.color(random.choice(self._COLORS))
      time.sleep(0.5)

wnd = Screen()
wnd.title("Simple Animation")

player = Turtle()
player.shapesize(5, 5, 10)
player.shape("square")
player.color("green")

wnd.onclick(player.goto)

NonBlockingLoop(player).start()

wnd.mainloop()
