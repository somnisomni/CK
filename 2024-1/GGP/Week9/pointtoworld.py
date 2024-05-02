def worldPointToScreenPoint(points, screenWidth, screenHeight):
  screenPoints = []
  for point in points:
    x, y = point
    screenX = (screenWidth / 2) + x
    screenY = (screenHeight / 2) - y
    screenPoints.append((screenX, screenY))
  return screenPoints

sW = 640
sH = 480
worldPoints = [
  (-100, 100),
  (-50, 50),
  (0, 0),
  (50, 50),
  (100, 100),
  (-100, -100),
  (-50, -50),
  (0, -50),
  (50, -50),
  (100, -100),
  (640, 480)
]

screenPoints = worldPointToScreenPoint(worldPoints, sW, sH)
print(screenPoints)
