#use this communication form

testvalue = 0
signal = "enter number"

def increment():
    global testvalue
    testvalue += 1

def write(number):
    return number


def show():
    return "hi i am a slave programm"

def showTestvalue():
    return testvalue

def getSignal():
    global signal
    return signal
