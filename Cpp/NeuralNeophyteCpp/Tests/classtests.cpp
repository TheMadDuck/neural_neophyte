#include "classtests.h"

ClassTests::ClassTests()
{
    t_tree();
}

#include "../tree.h"
bool ClassTests::t_tree()
{
    bool t_test = true;
    Tree tree;
    std::vector<int> path = {0, 3, 14, 9, 17};
    std::vector<int> path2 = {0, 3, 66, 6, 6};
    std::vector<int> path3 = {32, 212, 15, 221, 74, 23, 0, 2};

    int win = 1;
    int loss = 0;

    tree.addPathRec(path, win);
    tree.addPathRec(path2, loss);
    tree.addPathRec(path3, win);

    if(tree.getBestMove() != 32){
        t_test = false;
    }
    std::vector<double> a = tree.getProbabilities();
    std::vector<double> b ={0.5, 1};
    for (int var = 0; var < 2; ++var) {
        if (a[var] != b[var]){
            t_test = false;
        }
    }
    if(t_test == false){
        std::cout << "test failed" << std::endl;
    }
    else{
        std::cout << "test passed" << std::endl;
    }
    std::cout << t_test << std::endl;
    return t_test;
}

