a = { 100, 200, 200, 200, "hello", 1, 2, 3, 23, 3 }
print(a)

a.remove(200)
print(a)

print("hello" in a)
print(200 in a)

# === #

a = { 1, 2, 3, 4, 5, 6 }
b = { 4, 5, 6, 7, 8, 9 }

print(a.union(b))
print(a | b)
