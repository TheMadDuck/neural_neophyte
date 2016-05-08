import numpy as np
import random as rd

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
    #if numberModels == 0:
    #    numberModels = 1
array0 = np.empty(4, dtype=np.object)
array0[:] = [],[],[],[]
print(array0)
array0[0].append(3)
array0[0].append(3)
array0[0].append(3)
print(array0)
'''

print ("----------")


def nRand(border): #returns a integer beween 0 and border(booth inclusive). 0 is the least probable
    norm = np.random.normal(border, border/3, 1)
    norm = norm.astype(int)
    norm = abs(norm)
    sizeNorm = norm.size
    for i in range(sizeNorm):
        if norm[i] >= border:# > testen???
            norm[i] = rd.randint(0, border-1)
    return norm[0]
   
#print(bRand(10))

verteilung = np.zeros(10)
for i in range(10000):
    verteilung[nRand(10)] += 1
print(verteilung)

