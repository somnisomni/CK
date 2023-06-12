lista = [1, 1, 100, 100, "a", "b", "a", "a", "hello"]

new_list = []
for item in lista:
  if item in new_list:
    continue
  else:
    new_list.append(item)

print(new_list)

new_list2 = list(set(lista))
print(new_list2)
