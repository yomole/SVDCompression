# -*- coding: utf-8 -*-
"""
Created on Mon Apr 11 00:15:14 2022

@author: Nick
"""
import numpy as np
from numpy.linalg import eig
from numpy.linalg import norm


"""
Possible optimizations - filter out all the things that are possibly 0's to be just
0's and remove them outright (problems include modifying 'n' variable and being able
to distinguish between actual eigenvalues in all cases
"""

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
        #we should now have a sorted list
    def test(self):
        testMatrix = np.zeros((self.m, self.n))
        for i in range(self.n):
            #to get back, we want sigma * ui * viT
            testMatrix = testMatrix + self.sigma[i]*np.outer(self.u[:,i], self.v[:,i])
            
            #doing this entire summation should give us back our matrix
            #doing this up to a value k should give us the approximation
            #to get the best approx, we want these to be ordered by decreasing simga
        
        #print(testMatrix)
        return testMatrix
    #used to test the SVD approximation for a matrix (still really good)
    def testApprox(self):
        testMatrix = np.zeros((self.m, self.n))
        usedRange = min(self.n, 5)
        for i in range(usedRange):
            currSigma = self.tripleList[i].sigma
            currV = self.tripleList[i].v
            currU = self.tripleList[i].u
            testMatrix = testMatrix + currSigma*np.outer(currU,currV)
        return testMatrix
            

A = np.arange(10000).reshape((100,100))
#print(A)
TestSVD = SVD(A)
deltaA = A - TestSVD.test()
print(norm(deltaA)) #should be a small value that is about 0
approxDeltaA = A - TestSVD.testApprox()
print(norm(approxDeltaA))
                