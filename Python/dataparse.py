import matplotlib.pyplot as plt
import numpy as np
from scipy.ndimage import filters
datay = np.loadtxt("data.txt")
datax = np.arange(0,datay.shape[0])
#datay = filters.gaussian_filter(datay,60)
plt.figure()
plt.plot(datay)
#plt.figure()
#plt.plot(datax,filters.gaussian_filter(datay,15))
#plt.figure()
#plt.psd(datay)
plt.show()