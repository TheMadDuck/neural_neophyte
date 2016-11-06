#ifndef TREE_H
#define TREE_H
#include <vector>

class Tree
{
public:
    Tree(int move = -1, int depth = 0, int numberWon = 0, int numberPlayed = 0, std::vector<Tree*> childs = {}); //TODO move als -1 initialisieren?
    ~Tree(); //destructor
    Tree(const Tree &other); //copy constructor
    Tree(Tree&& other); //move constructor
    Tree& operator=(const Tree& other); //copy assignment
    Tree& operator=(Tree&& other); //move assignment

    int getNumberWon(int player);
    int getNumberPlayed();
    int getDepth();
    std::vector<Tree *> getChilds();
    void printTree();
    std::vector<int> getPreOrder(std::vector<int> preOrderList = {});
    //void addPath(std::vector<int> path, int winOrLoss);
    void addPathRec(std::vector<int> path, int winner);
    int getBestMove(int player);
    int getNextMove(int amountPosslibleMoves, int player);
    std::vector<double> getProbabilities(int player);
    void mergeTrees(Tree);
    void cutRoot(int nextRoot);
    Tree *lookUp(std::vector<int> path);
    void deleteTree(Tree *tree);

    bool Test();

private:
    int _move = -1;
    int _depth = 0;
//    int _numberWon = 0;
    std::vector<int> _numberWon = {0, 0}; // todo: make alloc dynamic.
    int _numberPlayed = 0;
    std::vector<Tree*> _childs = {};
};

#endif // TREE_H
