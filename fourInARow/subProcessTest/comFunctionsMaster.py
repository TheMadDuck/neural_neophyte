#use this comunication form

import comFunctionsSlave as sl

#sl.write(3)
#print(sl.show())

savetyIndex = 0
while(True):
    savetyIndex += 1
    if sl.getSignal() == "processing": # mayby set this at the middle or end of the function (naa auch net gut) to provide unnessesary amout of loops..
        continue
    if sl.getSignal() == "ended":
        break
    if sl.getSignal() == "enter number":
        output = sl.write(32)
        print (output)
    if sl.getSignal() == "i have a solution":
        sl.show()
    
    print("savetyIndex: " + str(savetyIndex))
    if savetyIndex > 25:
        break
