import random

options = ("rock", "paper", "scissors")
is_running = True

while is_running:

    player = None
    computer = random.choice(options)

    while player not in options:
        player = input("Select your choice (rock, paper, scissors): ")

    print(f"Players choice: {player}")
    print(f"Computer choice: {computer}")

    if player == computer:
        print("It's a tie!")
    elif player == "rock" and computer == "scissors":
        print("You win!")
    elif player =="paper" and computer == "rock":
        print("You win!")
    elif player == "scissors" and computer == "paper":
        print("You win")
    else:
        print("You lose!")
    
    answer = input("Yould you like to play again?: (y/n)")

    if answer == "n":
        is_running == False

print("Thanks for playing!")