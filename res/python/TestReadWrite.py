import struct
import numpy as np
from numpy.linalg import eig
from numpy.linalg import norm

"""
num = [2,4,6]
file = open("array.bin","wb")
arrayNum = bytearray(num)
file.write(arrayNum)
float_array = array('d', [2.2,4.4,6.6])
float_array.tofile(file)
file.close()

file = open("array.bin","rb")
number = list(file.read(3))
print(number)
float_array2 = array('d')
float_array2.fromstring(file.read())
file.close()
"""
"""
num = [2,4,6]
num2 = [2.2,4.4,6.6]
file = open("array2.bin","wb")
file.write(struct.pack('%si' % len(num), *num))
file.write(struct.pack('%sf' % len(num2), *num2))

file.close()

file2 = open("array2.bin","rb")
numList1 = struct.unpack('3i', file2.read(12))
numList2 = struct.unpack('3f', file2.read(12))

print(numList1)
print(numList2)
file2.close()
"""
#Going to try to start going file input and output correctly
class triple:
    def __init__(self, _sigma, _v, _u):
        #sigma is a scalar
        self.sigma = _sigma
        #v is a nx1 vector
        self.v = np.real(_v)
        #u is a mx1 vector
        self.u = np.real(_u)
    #This is all we need for a triple, will want to make a list of n triples and
    #sort by sigma
    
class SVD:
    def __init__(self, A):
        #A is a m x n matrix
        (self.m, self.n) = A.shape
        eigenMatrix = np.dot(np.transpose(A),A) #A^T A
        self.sigma, self.v = eig(eigenMatrix)
        #want to take square roots now
        """
        The eigenvalues are positive semidefinite, so taking abs should do nothing
        but help for the eigenvalues that are essentially 0 
        This will be even more inconsequential after we do the right ordering
        As then, the lower sigmas, especially 0, will contribute nothing
        """
        self.sigma = np.sqrt(np.abs(self.sigma)) 
        self.u = np.zeros((self.m,self.n))
        self.tripleList = []
        #This should compute n columns of A*v_i/sigma_i
        for i in range(self.n):
            self.u[:,i] = np.dot(A,self.v[:,i]) / self.sigma[i] 
            self.tripleList.append(triple(self.sigma[i], self.v[:,i], self.u[:,i]))
        #now we have all of our singular values
        #depending on how we want to store them, we can do a variety of different things
        """ Sorting goes here"""
        self.tripleList.sort(key= lambda x: x.sigma, reverse=True)
        
    def getKthApprox(self, k):
        truncList = []
        for i in range(k):
            truncList.append(self.tripleList[i])
        return truncList

def reconstruct(listOfTriples, rows, cols):
    outMatrix = np.zeros((rows, cols))
    for tripleVals in listOfTriples:
        outMatrix = outMatrix + tripleVals.sigma * np.outer(tripleVals.u, tripleVals.v)
    return outMatrix

k = 5
row = 10
col = 10
testMatrix = np.arange(100).reshape((row,col))
testSVD = SVD(testMatrix)
kthApprox = testSVD.getKthApprox(k)
fileWrite = open("testWrite.bin", "wb")
headerInfo = [k, row, col]
fileWrite.write(struct.pack('3i', *headerInfo))
for triples in kthApprox:
    fileWrite.write(struct.pack('f', triples.sigma))
    vList = triples.v.tolist()
    uList = triples.u.tolist()
    fileWrite.write(struct.pack('%sf' % col, *vList))
    fileWrite.write(struct.pack('%sf' % row, *uList))
    
fileWrite.close()
print("This is before reading file")
testApproxMatrix1 = reconstruct(kthApprox, row, col)
print(testApproxMatrix1)
print(norm(testMatrix-testApproxMatrix1))

"""Testing reading"""
fileRead = open("testWrite.bin", "rb")
newK, newRow, newCol = struct.unpack('3i', fileRead.read(12))
newTripleList = []
for kLoop in range(newK):
    newSigma = struct.unpack('f', fileRead.read(4))
    newV = struct.unpack('%sf' % newCol, fileRead.read(newCol*4))
    newU = struct.unpack('%sf' % newRow, fileRead.read(newRow*4))
    newTripleList.append(triple(newSigma, np.array(newV), np.array(newU)))
print("This is after reading the file")
testApproxMatrix2 = reconstruct(newTripleList, newRow, newCol)
print(testApproxMatrix2)
print(norm(testMatrix-testApproxMatrix2))
print("Comparing the 2 reconstructed matrices")
print(norm(testApproxMatrix1 - testApproxMatrix2))
fileRead.close()



