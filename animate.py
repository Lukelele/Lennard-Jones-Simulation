
import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation


#list all files in Output directory
files = os.listdir('Output')

for i, file in enumerate(files):
    print(str(i) + ": " + file)

index = int(input("Enter the index of the file you want to animate: "))

df = pd.read_csv("Output/" + files[index], low_memory=False)

file_list = files[index].split("_")

num_particles = int(file_list[0])
axisScale = float(file_list[1].split('.')[0])
frames = len(df['time'])

#create numpy array with shape (frames, 2)
x = np.zeros((num_particles, frames))
y = np.zeros((num_particles, frames))
z = np.zeros((num_particles, frames))

for i in range(num_particles):
    x[i] = df[f'atom{i}_x']
    y[i] = df[f'atom{i}_y']
    z[i] = df[f'atom{i}_z']

x = x.T
y = y.T
z = z.T


fig= plt.figure()
ax = fig.add_subplot(projection="3d")
points, = ax.plot([], [], [], 'o', markersize=5, color='red')
ax.set_xlim3d([-axisScale, axisScale])
ax.set_ylim3d([-axisScale, axisScale])
ax.set_zlim3d([-axisScale, axisScale])

#set the labels for the x y z axis
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')


#if x is single value (e.g. 1 or 2 or 3) then set_data will need square bracket set_data([x], [y]), if x is a list of values then set_data(x, y)
def update(i):
    points.set_data(x[i], y[i])
    points.set_3d_properties(z[i])
    ax.set_title(f"Time: {df['time'][i]} 10-9 s\Kinetic: {df['temperature'][i]}\n")
    return points,


ani = animation.FuncAnimation(fig, update, frames=frames, interval=20000/frames)
plt.show()


print(x.shape)
#ani.save('animation.mp4', writer='ffmpeg', fps=30)
