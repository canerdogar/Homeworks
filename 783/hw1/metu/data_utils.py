import scipy.io as sio # you may use scipy for loading your data
import cPickle as pickle # or Pickle library
import numpy as np
import os
from scipy import signal
import h5py

def load_dataset(filename):
 	"""Load your 'PPG to blood pressure' dataset"""
	# TODO: Fill this function so that your version of the data is loaded from a file into vectors
	X=[]
	Y=[]
	window_size=250
	# TODO: Fill this function so that your version of the data is loaded from a file into vectors
	with h5py.File(filename, 'r') as f:
		data = np.asarray(f[f.items()[1][1][3][0]][:])
		print data.shape
		#i2=0
		for index in range(0,data.shape[0],window_size):
			if index + window_size > data.shape[0]:
				break
			#print index , index+window_size
			X.append ( data[index:index+window_size, 0] )
			up_peaks = signal.find_peaks_cwt(np.array(data[index:index+window_size, 1]), np.arange(1, 50),  noise_perc=1)
			down_peaks = signal.find_peaks_cwt(-np.array(data[index:index+window_size, 1]), np.arange(1, 50),  noise_perc=1)
			Y.append( [np.average(np.array(data[index:index+window_size, 1])[up_peaks]), np.average(np.array(data[index:index+window_size, 1])[down_peaks]) ] )
			#i2+=1
			
	
	#print X
	#print "---------------------"
	#print Y
	X = np.array(X)
	Y = np.array(Y)
	return X, Y



if __name__ == '__main__':
	# TODO: You can fill in the following part to test your function(s)/dataset from the command line
	filename='...'
	X, Y = load_dataset(filename)

