import struct

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


