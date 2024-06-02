import numpy as np

def pointToMatrix3D(position: tuple[float, float, float]):
    return np.array([[1, 0, 0, position[0]],
                     [0, 1, 0, position[1]],
                     [0, 0, 1, position[2]],
                     [0, 0, 0, 1]])

def pointMatrixToScreenMatrix(matrix: np.ndarray, screenCenter: tuple[int, int]) -> np.ndarray:
    # origin: top-left
    return np.array([[matrix[0, 0], matrix[0, 1], matrix[0, 3] + screenCenter[0]],
                     [matrix[1, 0], matrix[1, 1], matrix[1, 3] + screenCenter[1]],
                     [0, 0, 1]])

def screenMatrixToPoint(matrix: np.ndarray) -> tuple[float, float]:
    return (matrix[0, 2], matrix[1, 2])


