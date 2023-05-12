import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# read data from excel file
filename = "RIOBUSES"
filepath = ".\data\\" + filename +".csv"
def load_data():
    if(filename == "LondonTrajectoriesDataset"):
        df = pd.read_csv(filepath)
        coors = df["coordinates"].tolist()
        coors = coors[0:-2]
        for i in range(len(coors)):
            coors[i] = ((coors[i].split(";"))[0])
        # coors = sorted(set(coors),key=coors.index)
        coors.sort()
        coors = pd.unique(coors).tolist()
        #---- test ----
        # df = pd.DataFrame({'Fruits': list(coors)})
        # df.to_csv('aaaa.csv', index=False)
        coor1 = []
        coor2 = []
        for i in range(len(coors)):
            coor1.append(coors[i].split(":")[0])
            coor2.append(coors[i].split(":")[1])
        return coor1, coor2
    elif(filename == "RIOBUSES"):
        df = pd.read_csv(filepath)
        coor1 = df["lat"].tolist()
        coor2 = df["lon"].tolist()
        return coor1, coor2
    else:
        print("wrong filename")
        exit()

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
plt.title(filename + ', '+str(coor1.shape[0]) + ' points')
plt.savefig(filename + '.png')
plt.show()
print("data printed successfully\n")

# print each cluster in a different color
# read cluster data from excel file
def print_clusters(filepath_points, filepath_clusters,fig_name):
    df = pd.read_csv(filepath_points)
    coor1 = df["X"].tolist()
    coor2 = df["Y"].tolist()    

    df = pd.read_csv(filepath_clusters)
    clusters = df["clusters"].tolist()
    clusters = list(map(int, clusters))
    minPts = df["minpts"].tolist()
    eps = df["eps"].tolist()
    # plot
    plt.scatter(coor1, coor2, c=clusters, cmap='rainbow')
    labels = ['Outlier']+['Cluster'+str(i) for i in range(1, max(clusters)+1)]

    color_map = plt.cm.get_cmap('rainbow', len(labels))

    legend_handles = []
    for i in range(len(labels)):
        legend_handles.append(plt.Rectangle((0, 0), 1, 1, color=color_map(i)))
    plt.legend(legend_handles, labels, loc=2)
    plt.xlabel('coor1')
    plt.ylabel('coor2')
    plt.title(fig_name + ', '+str(len(coor1)) + ' points, minPts:' + str(minPts[0]) + ", eps:" + str(eps[0]))
    plt.savefig(fig_name + '_clusters.png')
    # plt.show()
    plt.close()
    print(filepath_points + ": clusters printed successfully\n")

num_list = [24,48,96,192,384,768,1536,3072,6144,12288]
for i in num_list:
    filepath_points = ".\\data\GaussianPoints_" + str(i) + ".csv"
    filepath_clusters = ".\\random_clusters_" + str(i) + ".csv"
    fig_name = "GaussianPoints_" + str(i)
    print_clusters(filepath_points,filepath_clusters,fig_name)
