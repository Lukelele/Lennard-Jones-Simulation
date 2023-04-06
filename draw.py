import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation


df = pd.read_csv('output.csv')

# #create a 3d plot
# fig = plt.figure()
# ax = fig.add_subplot(projection='3d')

# x = df['atom0_x']
# y = df['atom0_y']
# z = df['atom0_z']


# def animate(num, data, line):
#     line.set_data(data[0:2, :num])
#     line.set_3d_properties(data[2, :num])
#     return line


# t = np.arange(0, 20, 0.2)

# line, = ax.plot(x, y, z)
# line_ani = animation.FuncAnimation(fig, animate, frames=len(t), fargs=(df, line), interval=1, blit=False)

# plt.show()


def animate(num, data1, line1, data2, line2):
    line1.set_alpha(0.7)
    line1.set_data(data1[0:2, :num])
    line1.set_3d_properties(data1[2, :num])
    
    line2.set_alpha(0.7)
    line2.set_data(data2[0:2, :num])
    line2.set_3d_properties(data2[2, :num])


t = np.arange(0, len(df['atom0_x']), 1)
x = df['atom0_x'] * 1e-9
y = df['atom0_y'] * 1e-9
z = df['atom0_z'] * 1e-9

x1 = df['atom1_x'] * 1e-9
y1 = df['atom1_y'] * 1e-9
z1 = df['atom1_z'] * 1e-9

data = np.array([x, y, z, t])
data1 = np.array([x1, y1, z1, t])

N = len(t)
fig = plt.figure()
ax = fig.add_subplot(projection='3d')

line, = plt.plot(data[0], data[1], data[2], lw=7, c='red')
line1, = plt.plot(data1[0], data1[1], data1[2], lw=7, c='blue')
line_ani = animation.FuncAnimation(fig, animate, frames=N, fargs=(data, line, data1, line1), interval=50, blit=False)

#animate another line using data1
# line1, = plt.plot(data1[0], data1[1], data1[2], lw=7, c='blue')
# line_ani1 = animation.FuncAnimation(fig, animate, frames=N, fargs=(data1, line1), interval=50, blit=False)

line_ani.save('animation.mp4', writer='ffmpeg', fps=30)

plt.show()
