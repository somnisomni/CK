from .base import BaseObjectWithVertices

class Cube(BaseObjectWithVertices):
  def regenerateVertices(self) -> None:
    #     4 --------- 5          y
    #    /           /|          ^
    #   0 --------- 1 |          |
    #   |           | |          /--->x
    #   | 6         | 7         /
    #   2 --------- 3          z

    wHalf = self.width / 2
    hHalf = self.height / 2
    dHalf = self.depth / 2
    wx, wy, wz = self.centerWorldPos

    self.vertices = [
      (wx - wHalf, wy + hHalf, wz + dHalf),   # 0 (front TL)
      (wx + wHalf, wy + hHalf, wz + dHalf),   # 1 (front TR)
      (wx - wHalf, wy - hHalf, wz + dHalf),   # 2 (front BL)
      (wx + wHalf, wy - hHalf, wz + dHalf),   # 3 (front BR)
      (wx - wHalf, wy + hHalf, wz - dHalf),   # 4 (back TL)
      (wx + wHalf, wy + hHalf, wz - dHalf),   # 5 (back TR)
      (wx - wHalf, wy - hHalf, wz - dHalf),   # 6 (back BL)
      (wx + wHalf, wy - hHalf, wz - dHalf)    # 7 (back BR)
    ]
