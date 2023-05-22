import random as rd

for _ in range(5):
  x = rd.random()
  print(x)

print("\n=====\n")

for _ in range(5):
  x = rd.uniform(1, 5)
  print(x)

print("\n=====\n")

for _ in range(5):
  x = rd.randrange(10, 20)
  print(x)

print("\n=====\n")

for _ in range(5):
  x = rd.randint(10, 20)
  print(x)
