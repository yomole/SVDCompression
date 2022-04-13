import numpy as np
print("Running test2.py (Arguments and Numpy Test!)")
print("\nNumpy Test:")
num = np.array([1, 2, 3, 5])
print("Numbers in array", len(num))
print("Index 0 + Index 2 =", num[0] + num[2])

print("\nArgument Test:")
print("Note: Arguments must be defined in a dictionary within C++ before the script is called.")
print("They may not be present in the python file (and you may get errors), but they will be there!")
for i in fileList:
    print(i)