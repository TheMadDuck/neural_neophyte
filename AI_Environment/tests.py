import unittest

import nRandomDistrib.nRand 
import eloRanking
import gameFlowClass
import tree

class SolutionTests(unittest.TestCase):

    def test1(self):
        for i in range(20):
            value = nRandomDistrib.nRand.nRand(19) 
            self.assertTrue(0 <= value <= 19)
            #print(value)

#----------------------------------------------------
    
    def test2(self):
        value = eloRanking.naiveElo(100, 100, 1)
        self.assertEqual((99.9, 100.1), value)

#----------------------------------------------------
    
    def test3(self):
        gClass = gameFlowClass.gameFlowClass(None, None)
        value = gClass.AI_Move(None, 1, 23, [0,1,2,3], None, 0.5, False)
        self.assertTrue((value == 0 or value == 1 or value == 2 or value == 3))

#----------------------------------------------------

    def test4(self):
        tClass = tree.gameTree()
        tClass.addPath([0, 3, 14, 9, 11], 1)
        tClass.addPath([0, 3, 66, 6, 6], 1)
        tClass.addPath([54, 342, 2432, 23, 2323, 35, 6344], 0)
        value = tClass.getTreePreOrder()
        self.assertEqual(value, [None, 0, 3, 14, 9, 11, 66, 6, 6, 54, 342, 2432, 23, 2323, 35, 6344] )

#----------------------------------------------------


if __name__ == '__main__':
    unittest.main()
