# 강의 듣다가 심심해서(?) 만든 코드

KEY = "somnixorSOMNIXOR"

# XOR encrypt
def xor(message: str, key: str) -> list:
  idx = 0
  encrypted = []

  for idx in range(len(message)):
    encrypted.append(ord(message[idx]) ^ ord(key[idx % len(key)]))

  return encrypted

# main
if __name__ == "__main__":
  print("KEY is '{}' (without quotes)".format(KEY))

  print("\nExample encrypted message (message is 'Example message'):")
  print(" ".join(map(hex, xor("Example message", KEY))))

  print("\nInput some messages to encrypt")

  while True:
    message = input(">> ")

    if not message: continue
    else: print(" ".join(map(hex, xor(message, KEY))), end="\n\n")
