class gameTree(object):
    def __init__(self):
        self.move = None
        self.depth = 0
        self.numberWon = 0
        self.numberPlayed = 0
        self.childs =[]
    
    def getNumberWon(self):
        return self.numberWon
    
    def getNumberPlayed(self):
        return self.numberPlayed

    def getDepth(self):
        return self.depth
    
    def printTree(self):
        print("move: " + str(self.move) + " depth: " + str(self.depth) + " numberPlayed: " + str(self.numberPlayed) + " numberWon: " + str(self.numberWon))
        if self.childs:
            for child in self.childs:
                child.printTree()

    def getTreePreOrder(self, preOrderList = []):
        preOrderList.append(self.move)
        if self.childs:
            for child in self.childs:
                child.getTreePreOrder(preOrderList)
        return preOrderList
    
    def addPath(self, path, winOrLoss):
        for move in path:
            pathExist = False
            for child in self.childs:
                if move == child.move: # es existiert schon ein solcher (teil-) pfad
                    pathExist = True
                    child.numberPlayed += 1
                    child.numberWon += winOrLoss #da win =1 und loss=0 werden nur wins gezählt.
                    self = child
            
            if pathExist == False:  #neuer zweig
                newChild = gameTree()
                newChild.move = move
                newChild.depth = self.depth + 1
                newChild.numberPlayed += 1
                newChild.numberWon += winOrLoss #da win =1 und loss=0 werden nur wins gezählt.
                self.childs.append(newChild)
                self = newChild

    def getBestMove(self):
        win_probability = 0
        bestMove = None
        for child in self.childs:
            if child.numberPlayed == 0:
                win_ratio = 0
            else:
                win_ratio = child.numberWon / child.numberPlayed 
            if (win_ratio >= win_probability):
                win_probability = win_ratio
                bestMove = child
        return bestMove.move 


    #TODO:
    def mergeTrees(self, tree):
        pass



"""
print("t1")
path = [0, 3, 14, 9, 11]
path2 = [0, 3, 66, 6, 6]
path3 = [54,342,2432,23,2323,35,6344]

print(path)
print(path2)
print(path3)

win = 1
loss = 0

tree = gameTree()
tree.addPath(path, win)
tree.addPath(path2, loss)
tree.addPath(path3, loss)
tree.printTree()
print(tree.getTreePreOrder())
print("t2")
print(tree.getBestMove())
"""
