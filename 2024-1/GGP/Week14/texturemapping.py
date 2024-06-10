import pygame
import numpy as np
import os

# Barycentric coordinates
def barycentric_coords_ext(triangle, point):
  vector_u = triangle[1] - triangle[0]
  vector_v = triangle[2] - triangle[0]
  vector_w = point - triangle[0]

  dot_uv = np.float64(vector_u.dot(vector_v))
  dot_vv = np.float64(vector_v.dot(vector_v))
  dot_uu = np.float64(vector_u.dot(vector_u))
  dot_wu = np.float64(vector_w.dot(vector_u))
  dot_wv = np.float64(vector_w.dot(vector_v))
  inv_denom = 1 / (dot_uv * dot_uv - dot_vv * dot_uu)

  lambda1 = (dot_wv * dot_uv - dot_wu * dot_vv) * inv_denom
  lambda2 = (dot_wu * dot_uv - dot_wv * dot_uu) * inv_denom
  lambda3 = 1.0 - lambda1 - lambda2

  # lamba1 + lambda2 + lambda3 = 1
  return (lambda3, lambda1, lambda2)

# bounding box
def compute_bounds(triangle):
  min_x = min(triangle[:, 0])
  max_x = max(triangle[:, 0])
  min_y = min(triangle[:, 1])
  max_y = max(triangle[:, 1])
  return min_x, max_x, min_y, max_y

# get texture pixel by UV
def texture_map(texture, uv):
  u, v = uv
  x = int(u * (texture.get_width() - 1))
  y = int((1-v) * (texture.get_height() - 1))
  return texture.get_at((x, y))

# render triangle
def render_triangle(screen, texture, triangle, triangle_uv, min_x, max_x, min_y, max_y):
  for x in range(min_x, max_x+1):
    for y in range(min_y, max_y+1):
      point = np.array([x, y])
      # barycentric 좌표계를 계산
      lambda1, lambda2, lambda3 = barycentric_coords_ext(triangle, point)

      # 만약 점이 삼각형 내부에 있다면 원래 0이어야 하나 오차 적용을 위해서 : -1.15e-16
      precision = -1.15e-16
      if lambda1 >= precision and lambda2 >= precision and lambda3 >= precision:
        # UV 좌표 보간
        uv = lambda1 * triangle_uv[0] + lambda2 * triangle_uv[1] + lambda3 * triangle_uv[2]
        # 텍스처 맵핑
        color = texture_map(texture, uv)
        # 픽셀 색상을 설정
        screen.set_at((x, y), color)

# init
pygame.init()

# screen
screen = pygame.display.set_mode((800, 600))

# texture
texture = pygame.image.load(os.path.join(os.path.dirname(os.path.abspath(__file__)), "ga.jpg"))

# triangles
triangle = np.array([(200, 200), (200, 400), (400, 200)])
triangleUV = np.array([(0, 1), (0, 0), (1, 1)])
bounds = compute_bounds(triangle)

triangle2 = np.array([(400, 200), (200, 400), (400, 400)])
triangle2UV = np.array([(1, 1), (0, 0), (1, 0)])
bounds2 = compute_bounds(triangle2)

# loop
running = True
while running:
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      running = False
  screen.fill((150,150,150))

  # render
  render_triangle(screen, texture, triangle, triangleUV, *bounds)
  render_triangle(screen, texture, triangle2, triangle2UV, *bounds2)

  # screen update
  pygame.display.flip()

# quit
pygame.quit()
