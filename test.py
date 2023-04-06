import matplotlib.pyplot as plt
import pandas as pd


df = pd.read_csv('/Users/lukelele/Documents/Scientific Computing/Year 2/Assessments/Assessment4/FinalAssessment/testout.csv', header=None)
print(df)

plt.plot(df[0], df[1])
plt.show()
