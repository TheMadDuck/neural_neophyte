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

    int getNumberWon();
    int getNumberPlayed();
    int getDepth();
    std::vector<Tree *> getChilds();
    void printTree();
    std::vector<int> getPreOrder(std::vector<int> preOrderList = {});
    //void addPath(std::vector<int> path, int winOrLoss);
    void addPathRec(std::vector<int> path, int winOrLoss);
    int getBestMove();
    int getNextMove();
    std::vector<double> getProbabilities();
    void mergeTrees(Tree);
    void cutRoot(int nextRoot);

    bool Test();

private:
    int _move = -1;
    int _depth = 0;
    int _numberWon = 0;
    int _numberPlayed = 0;
    std::vector<Tree*> _childs = {};
};

#endif // TREE_H
