import random


open('input.txt', 'w').close()
file = open("input.txt", "a")

limit = 2.8

for i in range(30):
    x = random.uniform(-limit, limit)
    y = random.uniform(-limit, limit)
    z = random.uniform(-limit, limit)
    file.write(f"{x},{y},{z},0,0,0,0,0,0\n")