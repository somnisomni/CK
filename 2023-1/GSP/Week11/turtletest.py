import turtle
from time import sleep

wnd = turtle.Screen()
wnd.setup()

wnd.title("Simple window")
wnd.bgcolor("lightblue")

tPen = turtle.Pen()
tPen.shape("triangle")

tPen.up()
tPen.forward(100)
tPen.left(90)
tPen.forward(100)
tPen.left(90)
tPen.forward(100)
tPen.left(90)

tPen.down()
tPen.forward(200)
tPen.right(30)
tPen.backward(100)

wnd.mainloop()
