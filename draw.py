import pandas as pd
import matplotlib.pyplot as plt


df = pd.read_csv('output.csv')

#create a 3d plot
fig = plt.figure()
ax = fig.add_subplot(projection='3d')

x = df['atom0_x']
y = df['atom0_y']
z = df['atom0_z']

ax.scatter(x, y, z, c='r', s=0.3)
plt.show()
