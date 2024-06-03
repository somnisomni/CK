import pygame
import numpy as np
import math
from pygame.locals import *

class Cube:
  def __init__(self, worldPos = (0, 0, 0), size = 100, color = (255, 128, 64)):
    self.worldPos = worldPos
    self.color = color
    self.size = size
    half = size / 2

    self.vertices = np.array([
      [-half, -half,  half, 1],  # FLB
      [ half, -half,  half, 1],  # FRB
      [ half,  half,  half, 1],  # FRT
      [-half,  half,  half, 1],  # FLT
      [-half, -half, -half, 1],  # BLB
      [ half, -half, -half, 1],  # BRB
      [ half,  half, -half, 1],  # BRT
      [-half,  half, -half, 1]   # BLT
    ])

    self.faces = np.array([
      [0, 1, 2],  # Front
      [2, 3, 0],  # Front
      [7, 6, 5],  # Back
      [5, 4, 7],  # Back
      [4, 5, 1],  # Right
      [1, 0, 4],  # Right
      [3, 2, 6],  # Left
      [6, 7, 3],  # Left
      [4, 0, 3],  # Top
      [3, 7, 4],  # Top
      [1, 5, 6],  # Bottom
      [6, 2, 1]   # Bottom
    ])

  def getFacePointsForRender(self, renderMatrix, viewportMatrix):
    # renderMatrix = projectionMatrix * viewMatrix * modelMatrix

    transformPoints = []
    for vertex in self.vertices:
      v = np.matmul(renderMatrix, vertex)  # to 2D coordinates
      v /= v[3]                            # to NDC
      v = np.matmul(viewportMatrix, v)     # to screen space
      transformPoints.append(v)

    facePoints = []
    for face in self.faces:
      points = []
      for i in face:
        points.append(transformPoints[i][:2])
      facePoints.append(points)

    return facePoints

def generateModelMatrix(translation: tuple[float, float, float], \
                        scale: tuple[float, float, float], \
                        rotationRadians: tuple[float, float, float]) -> np.ndarray:
  translateMatrix = np.array([
    [1, 0, 0, translation[0]],
    [0, 1, 0, translation[1]],
    [0, 0, 1, translation[2]],
    [0, 0, 0, 1]
  ])
  scaleMatrix = np.array([
    [scale[0], 0, 0, 0],
    [0, scale[1], 0, 0],
    [0, 0, scale[2], 0],
    [0, 0, 0, 1]
  ])
  rotationXMatrix = np.array([
    [1, 0, 0, 0],
    [0, np.cos(rotationRadians[0]), -np.sin(rotationRadians[0]), 0],
    [0, np.sin(rotationRadians[0]), np.cos(rotationRadians[0]), 0],
    [0, 0, 0, 1]
  ])
  rotationYMatrix = np.array([
    [np.cos(rotationRadians[1]), 0, np.sin(rotationRadians[1]), 0],
    [0, 1, 0, 0],
    [-np.sin(rotationRadians[1]), 0, np.cos(rotationRadians[1]), 0],
    [0, 0, 0, 1]
  ])
  rotationZMatrix = np.array([
    [np.cos(rotationRadians[2]), -np.sin(rotationRadians[2]), 0, 0],
    [np.sin(rotationRadians[2]), np.cos(rotationRadians[2]), 0, 0],
    [0, 0, 1, 0],
    [0, 0, 0, 1]
  ])
  rotationMatrix = np.matmul(rotationYMatrix, np.matmul(rotationXMatrix, rotationZMatrix))

  return np.matmul(translateMatrix, np.matmul(rotationMatrix, scaleMatrix))

def generateViewMatrix(cameraPosition: tuple[float, float, float], \
                       targetPosition: tuple[float, float, float]) -> np.ndarray:
  up = np.array([0, 1, 0])
  cam = np.array(list(cameraPosition))
  target = np.array(list(targetPosition))

  viewZ = target - cam
  viewZ = viewZ / np.linalg.norm(viewZ)
  viewX = np.cross(up, viewZ)
  viewX = viewX / np.linalg.norm(viewX)
  viewY = np.cross(viewZ, viewX)
  viewY = viewY / np.linalg.norm(viewY)

  camInvModelMatrix = np.array([
    [viewX[0], viewX[1], viewX[2], -np.dot(viewX, cam)],
    [viewY[0], viewY[1], viewY[2], -np.dot(viewY, cam)],
    [viewZ[0], viewZ[1], viewZ[2], -np.dot(viewZ, cam)],
    [0, 0, 0, 1]
  ])
  rot180Matrix = np.array([
    [-1, 0,  0, 0],
    [ 0, 1,  0, 0],
    [ 0, 0, -1, 0],
    [ 0, 0,  0, 1]
  ])

  return np.matmul(rot180Matrix, camInvModelMatrix)

def generateProjectionMatrix(fov: float, aspectRatio: float, near: float, far: float) -> np.ndarray:
  focalDistance = 1 / np.tan(math.radians(fov) / 2)
  zDiff = near - far

  return np.array([
    [focalDistance / aspectRatio, 0, 0, 0],
    [0, focalDistance, 0, 0],
    [0, 0, (far + near) / zDiff, (2 * far * near) / zDiff],
    [0, 0, -1, 0]
  ])

def generateViewportMatrix(screenWidth: int, screenHeight: int) -> np.ndarray:
  return np.array([
    [screenWidth / 2, 0, 0, screenWidth / 2],
    [0, -screenHeight / 2, 0, screenHeight / 2],
    [0, 0, 1, 0],
    [0, 0, 0, 1]
  ])

# Constants
WIDTH, HEIGHT = 800, 600
BGCOLOR = (105, 105, 105)
CAMERA_POSITION = (150, 200, 300)
CAMERA_TARGET = (0, 0, 0)
CAMERA_FOV = 60
CAMERA_NEAR = 0.1
CAMERA_FAR = 1000
FPS = 60

# Main
if __name__ == "__main__":
  # Initialize
  pygame.init()
  screen = pygame.display.set_mode((WIDTH, HEIGHT))
  currentFrame = 0

  # Cube
  cubes = [
    Cube((10, 10, 10), 100, (0, 0, 255)),
    Cube((-150, 150, -10), 50, (0, 255, 0))
  ]

  # Loop
  running = True
  while running:
    for event in pygame.event.get():
      if event.type == QUIT:
        running = False

    screen.fill(BGCOLOR)

    # Calc
    for cube in cubes:
      renderMatrix = np.matmul(generateProjectionMatrix(CAMERA_FOV, WIDTH / HEIGHT, CAMERA_NEAR, CAMERA_FAR), \
                              np.matmul(generateViewMatrix(CAMERA_POSITION, CAMERA_TARGET), \
                                        generateModelMatrix(cube.worldPos, (1, 1, 1), (0, 0, 0))))
      viewportMatrix = generateViewportMatrix(WIDTH, HEIGHT)

      # Render
      facePoints = cube.getFacePointsForRender(renderMatrix, viewportMatrix)
      for poly in facePoints:
        for point in poly:
          pygame.draw.circle(screen, (0, 0, 0), point[:2], 5)
        pygame.draw.polygon(screen, cube.color, poly, 1)

    CAMERA_POSITION = (200 * math.sin(currentFrame / FPS % FPS), 100 * math.sin(currentFrame / FPS % FPS), 300 * math.cos(currentFrame / FPS % FPS))
    pygame.display.flip()
    pygame.time.delay(1000 // FPS)
    currentFrame += 1

  pygame.quit()
