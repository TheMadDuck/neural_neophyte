import numpy as np


def incr(a, b):
    a[0].append(b)
    return a

b = [23,12,1]
arx = np.empty(2, dtype=np.object)
arx[:] = [], []

arx = incr(arx, b)
arx = incr(arx, [42, 42])
print(arx)

'''
list0 = [0,0,0]
list1 = [1,1,1]
#list1.append(0)
print(type(list0))
print(type(list1))
array0 = np.array((list0, list1) )
array0[0].append(42)
print(array0)
'''
'''
array0 = np.empty(4, dtype=np.object)
array0[:] = [],[],[],[]
print(array0)
array0[0].append(3)
array0[0].append(3)
array0[0].append(3)
print(array0)
'''


