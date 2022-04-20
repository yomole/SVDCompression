import numpy as np
from numpy.linalg import eig
import struct
import os


class triple:
    def __init__(self, _sigma, _v, _u):
        #sigma is a scalar
        self.sigma = float(_sigma)
        #v is a nx1 vector
        self.v = _v.real.astype(np.float)
        #u is a mx1 vector
        self.u = _u.real.astype(np.float)
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
            if self.sigma[i] == 0:
                self.u[:,i] = np.dot(A, self.v[:,i]) * 0.0
            else:
                self.u[:,i] = np.dot(A,self.v[:,i]) / self.sigma[i] 
                self.tripleList.append(triple(self.sigma[i], self.v[:,i], self.u[:,i]))
        #now we have all of our singular values
        """ Sorting goes here"""
        print("     sorting...")
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

#Get this from 12 + 4*4(1+row+col). One 4 for each matrix, other for bytes in a float
def getK(row, col, size):
    return (size - 12) // (16*(1+row+col))

def charArrayReader(charList):
    multiMatrix = np.zeros((sizeRow, sizeColumn, 4))
    counter = 0
    for r in range(sizeRow):
        for c in range(sizeColumn):
            for n in range(4):
                charThing = charList[counter]
                multiMatrix[r,c,n] = charThing
                multiMatrix[r,c,n] = charList[counter]
                counter = counter + 1
    return multiMatrix


#This recreates a matrix from the singular values 
def reconstruct(listOfTriples, rows, cols):
    outMatrix = np.zeros((rows, cols))
    for tripleVals in listOfTriples:
        outMatrix = outMatrix + tripleVals.sigma * np.outer(tripleVals.u, tripleVals.v)
    return outMatrix

#already expects a header to be written
def writeToFile(listOfTriples, rows, cols, fileWrite):
    for triples in listOfTriples:
        fileWrite.write(struct.pack('f', triples.sigma))
        vList = triples.v.tolist()
        uList = triples.u.tolist()
        fileWrite.write(struct.pack('%sf' % cols, *vList))
        fileWrite.write(struct.pack('%sf' % rows, *uList))

#outputs a list of each of the 4 RGBA matrices
def readFromFile(fileRead):
    newK, newRow, newCol = struct.unpack('3i', fileRead.read(12))
    outList = []
    for i in range(4):
        currTripleList = []
        for kLoop in range(newK):
            newSigmaBefore = struct.unpack('f', fileRead.read(4))
            print(newSigmaBefore)
            newSigma = sum(newSigmaBefore)
            newV = struct.unpack('%sf' % newCol, fileRead.read(newCol*4))
            newU = struct.unpack('%sf' % newRow, fileRead.read(newRow*4))
            currTripleList.append(triple(newSigma, np.array(newV), np.array(newU)))
        #after we get our triple list, we want to reconstruct, append, then move next
        outList.append(reconstruct(currTripleList, newRow, newCol))
    return outList #return a list of 4 matrices

#should create a file that can then be read by the c++ program
def toCSV(matrixList, fileLoc, rows, cols):
    fileLoc.write(f"{rows} {cols}\n")
    for r in range(rows):
        for c in range(cols):
            for n in range(4):
                currVal = round(matrixList[n][r,c])
                fileLoc.write(str(currVal))
                fileLoc.write(" ")
    return

""" Start of main method"""
#debugging statement
#cwd = os.getcwd()
#print("Current working directory: {0}".format(cwd))
sizeCol = sizeColumn
print("            Reading character array...")
bigMatrix = charArrayReader(charArray)
SVDList = [] #List of SVD objects
for i in range(4):
    print("             Compressing...")
    SVDList.append(SVD(bigMatrix[:,:,i]))

writeRow = SVDList[0].m
writeCol = SVDList[0].n
k = getK(writeRow, writeCol, fileLim)
#Now for each SVD in the list, we want to get its kth approx and then write it
fileWrite = open(fileLocationBin, "wb")
headerInfo = [k, sizeRow, sizeCol]
print("             Writing binary file...")
fileWrite.write(struct.pack('3i', *headerInfo))
for decomp in SVDList:
    currTripleList = decomp.getKthApprox(k)
    writeToFile(currTripleList, sizeRow, sizeCol, fileWrite)

fileWrite.close()

"""Now time to decode. Independent of everything above except the file"""
fileRead = open(fileLocationBin, "rb")
print("             Reading binary file...")
matrixList = readFromFile(fileRead)
readRow, readCol = matrixList[0].shape
fileRead.close()


"""Now time to export from here to a csv to present in c++"""
fileWriteCSV = open(fileLocationCSV, 'w')
print("             Writing CSV file...")
toCSV(matrixList, fileWriteCSV, readRow, readCol)
fileWriteCSV.close()

        
