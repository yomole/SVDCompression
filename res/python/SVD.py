import numpy as np
from numpy.linalg import eig
from numpy.linalg import norm
import struct

"""NEED TO REMOVE"""
#sizeRow = 10
#sizeColumn = 10
#fileLim = 10
#charArray = [1,3,4,344]
"""NEED TO REMOVE"""

class triple:
    def __init__(self, _sigma, _v, _u):
        #sigma is a scalar
        self.sigma = _sigma
        #v is a nx1 vector
        self.v = _v
        #u is a mx1 vector
        self.u = _u
    #This is all we need for a triple, will want to make a list of n triples and
    #sort by sigma

#this will be a class that takes in a matrix and stores it as an "SVD" object
#constructor will take in a matrix A of dimensions m x n and construct the 
#sigma, u, and v vectors stored together?
#might also make a helper object "Triplet" to store each, sorted by sigma
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
    
    
#sizeRow and sizeColumn are imported from c++
def breakLine(inputString):
    outList = []
    currWord = ""
    for elm in inputString:
        if not elm == " ":
            currWord = currWord + elm
        else: #once we hit a space, we append it to the list and restart
            outList.append(currWord)
            currWord = ""
    outList.append(currWord)
    return outList

def getK(row, col, size):
    return (size - 12) // (4*(1+row+col))

"""
class fileReader:
    def __init__(self, file):
        file_obj = open(file, "r")
        header = file_obj.readline()
        headerList = breakLine(header)
        rows = int(headerList[0])
        columns = int(headerList[1])
        #now start the main loop
        multiMatrix = np.zeros((rows, columns, 4))
        nextLine = ""
        nextList = []
        for n in range(4):
            for i in range(rows):
                nextLine = file_obj.readline()
                nextList = breakLine(nextLine)
                for j in range(columns):
                    multiMatrix[i,j,n] = 
"""

def charArrayReader(charList):
    multiMatrix = np.zeros((sizeRow, sizeColumn, 4))
    counter = 0
    for r in range(sizeRow):
        for c in range(sizeColumn):
            for n in range(4):
                counter = counter + 1
                multiMatrix[r,c,n] = charList[counter]
    return multiMatrix




#now to break down each matrix into its components and send them out piece by piece
""" Start of main method"""

bigMatrix = charArrayReader(charArray)
k = getK(sizeRow, sizeColumn, fileLim)
print("Printing k value")
print(k)
print("Printing each matrix")
for i in range(4):
    print(bigMatrix[:,:,i])


"""
bigMatrix = charArrayReader(charArray)
SVDList = []
for i in range(4):
    SVDList.append(SVD(bigMatrix[:,:,i]))
k = getK(fileLim)
#double list of triples goes here
doubleList = []
for matrix in SVDList:
    doubleList.append(matrix.getKthApprox(k))
"""
        
        
