import random

while True:
    dice = input("Roll the dice> (y/n): ").lower()
    if dice == "n":
        print("Thanks for playing")
        break
    elif dice == "y":
        dice1 = random.randint(1, 6)
        dice2 = random.randint(1, 6)
        print(f"({dice1}, {dice2})")
    else:
        print("Invalid choice!")