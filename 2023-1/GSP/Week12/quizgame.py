quiz = {
  "Q1": {
    "question": "대한민국의 수도는?",
    "answer": "서울"
  },
  "Q2": {
    "question": "게임스쿨 원장님 이름은?",
    "answer": "염동현"
  },
  "Q3": {
    "question": "대한민국에서 게임으로 유명한 대학교는?",
    "answer": "청강문화산업대학교"
  }
}

score = 0

for q in quiz:
  print(quiz[q]["question"])
  ans = input("정답은?: ")

  if ans == quiz[q]["answer"]:
    print("정답!")
    score += 1
  else:
    print("오답...")
  print()

print(f"점수: {score}점")
