import numpy as np
import gameFlowClass as gFC  # TODO Warning! circle import.
import games.fourInARow as gL
import copy
import tree as tr
import random as rd

class gameTree(object):
    def __init__(self):
        self.move = None
        self.numberWon = 21
        self.numberPlayed = 0
        self.childs = []
    def getNumberWon(self):
        return self.numberWon
    def printTree(self):
        if self.childs:
            for child in self.childs:
                print(self.move)
                child.printTree()
#    def addPath(self, path):
#        for move in path:
#            for child in self.childs:
#                if move == child:

"""
zugReihenfolge = [3, 4, 4, 1, 5, 0, 1]
zugReihenfolge2 = [23, 24, 24, 21, 25, 230, 11]
root = gameTree()
tree = gameTree()
root.childs.append(tree)

for i in zugReihenfolge:
    tree.move = i
    subTree = gameTree()
    tree.childs.append(subTree)
    tree = subTree

tree = gameTree()
root.childs.append(tree)
for i in zugReihenfolge2:
    tree.move = i
    subTree = gameTree()
    tree.childs.append(subTree)
    tree = subTree


root.printTree()
print (root.childs)
"""

"""
for i in reversed(zugReihenfolge):
    topTree = gameTree()
    topTree.move = i
    topTree.childs.append(tree)
    tree = topTree

for i in reversed(zugReihenfolge2):
    topTree = gameTree()
    topTree.move = i
    topTree.childs.append(tree)
    tree = topTree
"""



#TODO: difer between pure mcts(complete random, [possible with NNs?]) and exploited mcts (tree based)
def mcts(field, tree, legalMoves, classifier, players, roundNumber, playerNumber, randomMoveProba): #without Tree!
    gameNumber = 3  # how many games should be played per move . maybe need a better name for parameter
    winProbability = np.zeros(len(legalMoves))
    for move in range(len(legalMoves)):
        wins = 0
        for game in range(gameNumber):
            fieldCopy = copy.deepcopy(field)
            tempGameLogic = gL.gameLogic()
            tempGameFlow = gFC.gameFlowClass(classifier, tempGameLogic, fieldCopy, roundNumber) 
            path = tempGameFlow.gameFlow(players, False, [move])
            if(tempGameFlow.getWinner() == playerNumber):
                wins += 1   # MAYBE * (0.5 ^ tiefe)  SO DEEPER WINS ARE NOT AS IMPORTANT AS SHALLOW ONES (???)
            del fieldCopy
            del tempGameLogic
            del tempGameFlow
        winProbability[move] = float(wins)/float(gameNumber)
    allMaximalValues = np.argwhere(winProbability == np.amax(winProbability))
    return rd.choice(allMaximalValues)[0]
    #return winProbability.argmax(axis=0)


def pure_mcts(field, tree, legalMoves, classifier, players, roundNumber, playerNumber, randomMoveProba): #with tree but without exploitation(should have same result as mcts)!
    gameNumber = 3
    mcts_tree = tr.gameTree()
    for i in range(gameNumber):
        move = rd.choice(legalMoves)
        fieldCopy = copy.deepcopy(field)
        tempGameLogic = gL.gameLogic()
        tempGameFlow = gFC.gameFlowClass(classifier, tempGameLogic, fieldCopy, roundNumber) 
        path = tempGameFlow.gameFlow(players, False, [move])
        if(tempGameFlow.getWinner() == playerNumber):
            mcts_tree.addPath(path, 1)
        else:
            mcts_tree.addPath(path, 0)
        del fieldCopy
        del tempGameLogic
        del tempGameFlow
    return mcts_tree.getBestMove()


#TODO: why does AI_Move provide self.classifier + 2* classifierModel?? should provide who's turn is next.
def exploited_mcts(field, oldTree, legalMoves, classifier, players, roundNumber, playerNumber, randomMoveProba):

    if (oldTree):
        mcts_tree = oldTree
    else:
        mcts_tree = tr.gameTree()
    
    for move in legalMoves: # first every move is played at least once
        fieldCopy = copy.deepcopy(field)
        tempGameLogic = gL.gameLogic()
        tempGameFlow = gFC.gameFlowClass(classifier, tempGameLogic, fieldCopy, roundNumber) 
        path = tempGameFlow.gameFlow(players, False, [move])
        if(tempGameFlow.getWinner() == playerNumber):
            #print ("yeaaaaaaaaaaaaaaaaaaaaaaaaaaa 1:" + str(path))
            mcts_tree.addPathRec(path, 1)
        else:
            #print ("yeaaaaaaaaaaaaaaaaaaaaaaaaaaa 2:" + str(path))
            mcts_tree.addPathRec(path, 0)
        del fieldCopy
        del tempGameLogic
        del tempGameFlow
            

    gameQuantity = 8  # then a few extra games are played
    for i in range(gameQuantity):
        move = mcts_tree.getNextMove()
        fieldCopy = copy.deepcopy(field)
        tempGameLogic = gL.gameLogic()
        tempGameFlow = gFC.gameFlowClass(classifier, tempGameLogic, fieldCopy, roundNumber) 
        path = tempGameFlow.gameFlow(players, False, [move])
        if(tempGameFlow.getWinner() == playerNumber):
            #print ("yeaaaaaaaaaaaaaaaaaaaaaaaaaaa 3:" + str(path))
            mcts_tree.addPathRec(path, 1)
        else:
            #print ("yeaaaaaaaaaaaaaaaaaaaaaaaaaaa 4:" + str(path))
            mcts_tree.addPathRec(path, 0)
        del fieldCopy
        del tempGameLogic
        del tempGameFlow

    #TODO more loops with the best moves until only one is THE best move
    print("probas")
    print(mcts_tree.getChilds())
    print(mcts_tree.getProbabilities()) 
    return mcts_tree.getBestMove()

    """
    t = tree.gameTree()
    #t.getNextMove()
    for move in range(gameQuantity):
        fieldCopy = copy.deepcopy(field)
        tempGameLogic = gL.gameLogic()
        tempGameFlow = gFC.gameFlowClass(classifier, tempGameLogic, fieldCopy, roundNumber, 0.5)
        path = tempGameFlow.gameFlow(players, False, [move]) #check if path size is odd or even...

        if(tempGameFlow.getWinner == playerNumber):
            t.addPath(path, 1)
        else:
            t.addPath(path, 0)

        del fieldCopy
        del tempGameLogic
        del tempGameFlow
    return 0
    """

"""
def minmax(position, depth):
    if position = won:
        return 1
    else if(position = lost):
        return -1
    else:
        return 0
    
    if depth == 0;
        return evalScore

    bestScore = -99999999

    for move in possibleMoves:
        subScore = -minmax(position(mitMove) , depth -1)
        if subScore > bestScore:
            bestScore = subScore

    return bestScore


# oder so... :P
"""
