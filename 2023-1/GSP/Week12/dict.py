grades = { "Kang": 95, "Kim": 90 }
print(grades)
print(grades["Kang"])

grades["Hong"] = 99
print(grades)

grades["Park"] = { "Python": 88, "3D Modeling": 98, "Concept Design": 95 }
print(grades)

grades["Choi"] = [100, 50, 50]
print(grades)

print(grades["Park"]["Python"])
print(grades["Choi"][0])
