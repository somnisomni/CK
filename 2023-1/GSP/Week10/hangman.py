import random

words = ["apple", "banana", "orange", "grape", "pineapple"]
answer = random.choice(words)

player_guesses = []
guess_count = 0

while True:
  has_missing = False
  for char in answer:
    if char in player_guesses:
      print(char, end=" ")
    else:
      print("_", end=" ")
      has_missing = True

  if not has_missing:
    print("\n추측 성공!")
    break

  guess = input("\n한 글자를 추측하세요: ")
  player_guesses.append(guess)
  if guess not in answer:
    print("입력한 문자가 포함되지 않습니다.")
    guess_count += 1

  if len(answer) < guess_count:
    print("\n게임 종료. 정답: {}".format(answer))
    break
