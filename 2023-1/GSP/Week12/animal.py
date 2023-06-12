class Dog:
  def __init__(self, name, age):
    self.name = name
    self.age = age

  def bark(self):
    print(f"{self.name}: 멍멍! 멍멍멍!")

  def draw(self):
    print(f"{self.name} ({self.age} years old)")

class Cat:
  def __init__(self, name, color):
    self.name = name
    self.color = color

  def bark(self):
    print(f"{self.name}: 야옹! 야옹야옹!")

  def draw(self):
    print(f"{self.name} (color: {self.color})")

whiteDog = Dog("White Dog", 2)
whiteDog.bark()
whiteDog.draw()

blackDog = Dog("Black Dog", 4)
blackDog.bark()
blackDog.draw()

whiteCat = Cat("White Cat", "White")
blackCat = Cat("Nabi", "Black")

whiteCat.bark()
whiteCat.draw()
blackCat.bark()
blackCat.draw()
