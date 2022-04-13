# -*- coding: utf-8 -*-
"""
Created on Mon Apr 11 00:15:14 2022

@author: Nick
"""
import numpy as np
from numpy.linalg import eig

#do we want to implement a heap or BST to keep the things sorted?

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
        #This should compute n columns of A*v_i/sigma_i
        for i in range(self.n):
            self.u[:,i] = np.dot(A,self.v[:,i]) / self.sigma[i] 
        #now we have all of our singular values
        #depending on how we want to store them, we can do a variety of different things
        """ Sorting goes here"""
    def test(self):
        testMatrix = np.zeros((self.m, self.n))
        for i in range(self.n):
            #to get back, we want sigma * ui * viT
            testMatrix = testMatrix + self.sigma[i]*np.outer(self.u[:,i], self.v[:,i])
            #doing this entire summation should give us back our matrix
            #doing this up to a value k should give us the approximation
            #to get the best approx, we want these to be ordered by decreasing simga
        print(testMatrix)
        return testMatrix
            

A = np.arange(10).reshape((2,5))
print(A)
TestSVD = SVD(A)
TestSVD.test()
deltaA = A - TestSVD.test()
print(deltaA)
                