
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation


df = pd.read_csv('output.csv', low_memory=False)


num_particles = 2

frames = len(df['time'])

#create numpy array with shape (frames, 2)
x = np.zeros((num_particles, frames))
y = np.zeros((num_particles, frames))
z = np.zeros((num_particles, frames))

for i in range(num_particles):
    x[i] = df[f'atom{i}_x'] * 1e-9
    y[i] = df[f'atom{i}_y'] * 1e-9
    z[i] = df[f'atom{i}_z'] * 1e-9

x = x.T
y = y.T
z = z.T


axisScale = 4e-10

fig= plt.figure()
ax = fig.add_subplot(projection="3d")
points, = ax.plot([], [], [], 'o', markersize=5, color='red')
ax.set_xlim3d([-axisScale, axisScale])
ax.set_ylim3d([-axisScale, axisScale])
ax.set_zlim3d([-axisScale, axisScale])


#if x is single value (e.g. 1 or 2 or 3) then set_data will need square bracket set_data([x], [y]), if x is a list of values then set_data(x, y)
def update(i):
    points.set_data(x[i], y[i])
    points.set_3d_properties(z[i])

    return points,


ani = animation.FuncAnimation(fig, update, frames=frames, interval=5000/frames)
plt.show()


#ani.save('animation.mp4', writer='ffmpeg', fps=30)
