import numpy as np
import matplotlib.pyplot as plt
import csv

with open('results.csv', newline='') as f:
    reader = csv.reader(f)
    results_list = []
    for row in reader:
        results_list.append(int(row[0]))
    f.close()

results_array = np.array(results_list)
xvals = np.array([1, 2, 4, 8, 16, 32, 64])
plt.bar(xvals, results_array, facecolor="red")
plt.title("Problem 2 Speed for ax + y")
plt.xlabel("Block Size")
plt.ylabel("Speed in MFLOPS")
plt.show()