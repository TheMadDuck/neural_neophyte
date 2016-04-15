#!/usr/bin/env python

import subprocess
import os



a = subprocess.Popen(["python", "-c", "import subprocessA; subprocessA.getNumber()"], stdout=subprocess.PIPE)
print("output (1st line):")
print(a.stdout.readline())
print("output (2nd line):")
print(a.stdout.readline())


a = subprocess.Popen(["python", "-c", "import subprocessA; subprocessA.setNumber()"], stdout=subprocess.PIPE, stdin=subprocess.PIPE)
gumb = "gumba"
a.stdin.write(gumb.encode('utf-8'))
#kra = a.communicate(input=gumb.encode('utf-8'))
print("output of setNumber() function")
x = a.stdout.readline()
print(x)


########################################
'''
#print(os.getcwd())
#print(os.path(__file__))


#subprocess.call("ls")
#subprocess.call("python", os.getcwd() + "/subprocessA.py")
#a = subprocess.call(["python", "subprocessA.py"],stdout=subprocess.PIPE)
a = subprocess.Popen(["python", "-c", "import subprocessA; subprocessA.getNumber()"], stdout=subprocess.PIPE)
#print(a)
#a.wait()
print("output (1st line):")
print(a.stdout.readline())
print("output (2nd line):")
print(a.stdout.readline())


a = subprocess.Popen(["python", "-c", "import subprocessA; subprocessA.setNumber()"], stdout=subprocess.PIPE, stdin=subprocess.PIPE)
gumb = "gumba"
#a.stdin.write(gumb.encode('utf-8'))
kra = a.communicate(input=gumb.encode('utf-8'))
print("output of setNumber() function")
print(kra)
#print(a.stdout.readline())
#subprocess.call(["python", "subprocessA.py", "getNumber()"])
#output = subprocess.check_output(["python", "subprocessA.py"])

#print("the output is:")
#print(output)

'''



'''
Inhalt der subprocess datei:
import numpy as np 
for i in range(10): 
    print("i am a subProcess") 
         
def getNumber(): 
    return 1337 
              
def setNumber(): 
    number = input("set new Number") 
    print(number) 
'''

