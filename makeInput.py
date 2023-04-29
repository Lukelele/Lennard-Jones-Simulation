import math
import random


open('input.txt', 'w').close()
file = open("input.txt", "a")

limit = 1e-9

#to make sure the particles are not generated at the boudaries
limit = limit * 0.9
v_limit = 0
num_particles = 9


# if 2 * limit / (num_particles ** (1/3)) < 3e-10:
#     print("Error: particles are too close to each other")
# else:
#     count = 0
#     for i in range(math.ceil(num_particles ** (1/3))):
#         for j in range(math.ceil(num_particles ** (1/3))):
#             for k in range(math.ceil(num_particles ** (1/3))):
#                 if count >= num_particles:
#                     break
                
#                 x = limit * 2 / (num_particles ** (1/3)) * i - limit
#                 y = limit * 2 / (num_particles ** (1/3)) * j - limit
#                 z = limit * 2 / (num_particles ** (1/3)) * k - limit


#                 vx = random.uniform(-v_limit, v_limit)
#                 vy = random.uniform(-v_limit, v_limit)
#                 vz = random.uniform(-v_limit, v_limit)
#                 file.write(f"{x},{y},{z},{vx},{vy},{vz},0,0,0\n")
#                 # file.write(f"{x},{y},{z},0,0,0,0,0,0\n")
#                 count += 1


for i in range(num_particles):
    x = random.uniform(-limit, limit)
    y = random.uniform(-limit, limit)
    z = random.uniform(-limit, limit)

    vx = random.uniform(-v_limit, v_limit)
    vy = random.uniform(-v_limit, v_limit)
    vz = random.uniform(-v_limit, v_limit)
    file.write(f"{x},{y},{z},{vx},{vy},{vz},0,0,0\n")