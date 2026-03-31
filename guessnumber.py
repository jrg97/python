import random

num = random.randrange(0, 100)
print(num)
atempts = 0

while True:
    guess = int(input("Guess the number: "))
    if guess > num:
        print("Too high")
        atempts += 1
    elif guess < num:
        print("Too low")
        atempts += 1
    else:
        print(f"Congratulations! You guessed in {atempts} atempts ")
        break


