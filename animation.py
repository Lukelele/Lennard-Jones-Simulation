
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation



# N = len(t)
# fig = plt.figure()
# ax = fig.add_subplot(projection='3d')

# def animate(num, data1, line1, data2, line2):

#     line1.set_alpha(0.7)
#     line1.set_data(data1[0:2, :num])
#     line1.set_3d_properties(data1[2, :num])
    
#     line2.set_alpha(0.7)
#     line2.set_data(data2[0:2, :num])
#     line2.set_3d_properties(data2[2, :num])


# line1, = plt.plot(data1[0], data1[1], data1[2], lw=7, c='red')
# line2, = plt.plot(data2[0], data2[1], data2[2], lw=7, c='blue')
# line_ani = animation.FuncAnimation(fig, animate, frames=N, fargs=(data1, line1, data2, line2), interval=5, blit=False)

# # line_ani.save('animation.mp4', writer='ffmpeg', fps=30)

# plt.show()



df = pd.read_csv('output.csv')

frames = len(df['time'])

#create numpy array with shape (frames, 2)
x = np.zeros((2, frames))
y = np.zeros((2, frames))
z = np.zeros((2, frames))

x[0] = df['atom0_x'] * 1e-9
y[0] = df['atom0_y'] * 1e-9
z[0] = df['atom0_z'] * 1e-9

x[1] = df['atom1_x'] * 1e-9
y[1] = df['atom1_y'] * 1e-9
z[1] = df['atom1_z'] * 1e-9


x = x.T
y = y.T
z = z.T


axisScale = 5e-10

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


ani = animation.FuncAnimation(fig, update, frames=frames, interval=3000/frames)
# plt.show()

ani.save('animation.mp4', writer='ffmpeg', fps=120)

