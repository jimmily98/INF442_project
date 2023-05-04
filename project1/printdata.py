import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# read data from excel file
filepath = ".\data\LondonTrajectoriesDataset.csv"
def load_data():
    df = pd.read_csv(filepath)
    coors = df["coordinates"].tolist()
    coors = coors[0:-2]
    for i in range(len(coors)):
        coors[i] = ((coors[i].split(";"))[0])
    coors = sorted(set(coors),key=coors.index)
    coor1 = []
    coor2 = []
    for i in range(len(coors)):
        coor1.append(coors[i].split(":")[0])
        coor2.append(coors[i].split(":")[1])
    return coor1, coor2

coor1, coor2 = load_data()
# to list of doubles
coor1 = list(map(float, coor1))
coor2 = list(map(float, coor2))
# min-max normalization to [0,1]
coor1 = (coor1 - np.min(coor1)) / (np.max(coor1) - np.min(coor1))
coor2 = (coor2 - np.min(coor2)) / (np.max(coor2) - np.min(coor2))
# plot
plt.plot(coor1, coor2, 'ro')
plt.xlabel('coor1')
plt.ylabel('coor2')
plt.title('LondonTrajectoriesDataset')
plt.show()
print("data printed successfully\n")

