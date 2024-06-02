import numpy as np
from util import pointToMatrix3D

class BaseObject:
  centerWorldPos: tuple[float, float, float] = (0, 0, 0)

  def __init__(self, \
               centerWorldPos: tuple[float, float, float] = (0, 0, 0)):
    self.centerWorldPos = centerWorldPos

  def move(self, dx: float = 0, dy: float = 0, dz: float = 0) -> None:
    self.centerWorldPos = (self.centerWorldPos[0] + dx, \
                           self.centerWorldPos[1] + dy, \
                           self.centerWorldPos[2] + dz)

  def posToWorldMatrix(self) -> np.ndarray:
    return pointToMatrix3D(self.centerWorldPos)


class BaseObjectWithVertices(BaseObject):
  width: float = 1
  height: float = 1
  depth: float = 1
  vertices: list[tuple[float, float, float]] = []

  def __init__(self, \
               centerWorldPos: tuple[float, float, float] = (0, 0, 0), \
               width: float = 1, \
               height: float = 1, \
               depth: float = 1):
    super().__init__(centerWorldPos)
    self.width = width
    self.height = height
    self.depth = depth
    self.regenerateVertices()

  def move(self, dx: float = 0, dy: float = 0, dz: float = 0) -> None:
    super().move(dx, dy, dz)
    self.regenerateVertices()

  def verticesToWorldMatrix(self) -> np.ndarray:
    matrices = []
    for vertex in self.vertices:
      matrices.append(pointToMatrix3D(vertex))
    return np.array(matrices)

  def regenerateVertices(self) -> None:
    pass
