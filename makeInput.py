import math
import random


open('input.txt', 'w').close()
file = open("input.txt", "a")

limit = 1e-9

#to make sure the particles are not generated at the boudaries
limit = limit * 0.9
v_limit = 100
num_particles = 100


particle_list = []

count = 0
buffer = 0
loop_break = False

while count < num_particles:
    x = random.uniform(-limit, limit)
    y = random.uniform(-limit, limit)
    z = random.uniform(-limit, limit)

    for particle in particle_list:
        if (x - particle[0]) ** 2 + (y - particle[1]) ** 2 + (z - particle[2]) ** 2 < 3.4e-10 ** 2:
            loop_break = True
            break

    if loop_break:
        loop_break = False
        buffer += 1
        continue

    if buffer > 100:
        print("Error: particles are too close to each other")
        break

    particle_list.append((x, y, z))

    vx = random.uniform(-v_limit, v_limit)
    vy = random.uniform(-v_limit, v_limit)
    vz = random.uniform(-v_limit, v_limit)
    file.write(f"{x},{y},{z},{vx},{vy},{vz},0,0,0\n")

    count += 1
    buffer = 0

