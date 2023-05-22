def add(a, b):
  return a + b

def minus(a, b):
  return a - b

def multiply(a, b):
  return a * b

def divide(a, b):
  if b == 0:
    return None
  else:
    return a / b

if __name__ == "__main__":
  print(multiply(10, 5))
