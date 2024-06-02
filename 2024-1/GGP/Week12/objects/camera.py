from .base import BaseObject
import numpy as np
from util import pointToMatrix3D

class Camera(BaseObject):
  rotation: tuple[float, float, float] = (0, 0, 0)
  fov: float = 90

  def __init__(self, \
               centerWorldPos: tuple[float, float, float] = (0, 0, 10), \
               rotation: tuple[float, float, float] = (0, 0, 0), \
               fov: float = 90):
    super().__init__(centerWorldPos)
    self.rotation = rotation  # All-zero means the camera is facing the negative Z-axis (XY plane)
    self.fov = fov

  def posToViewMatrix(self) -> np.ndarray:
    return pointToMatrix3D(tuple(map(lambda i: -i, self.centerWorldPos)))
