from cs50 import get_float

input = get_float("Change: ")
while input < 0:
    input = get_float("Change: ")

counter = 0
coins = [25, 10, 5, 1]

money = int(input * 100)

for coin in coins:
    while money >= coin:
        money -= coin
        counter += 1

print(counter)
