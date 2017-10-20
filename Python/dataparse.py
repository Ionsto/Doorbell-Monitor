import matplotlib.pyplot as plt
import numpy as np

datay = np.loadtxt("data.txt")
datax = np.arange(0,datay.shape[0])
plt.plot(datax,datay)
plt.show()