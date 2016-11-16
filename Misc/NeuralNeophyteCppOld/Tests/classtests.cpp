/*   Copyright (C) 2016 by Daniel M.H. Noll                                *
 *   Author: Daniel Noll                                                   *
 *                                                                         *
 *   Email: sport.mann@gmx.de                                              *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * Redistribution and use in source and binary forms, with or without      *
 * modification, are permitted provided that the following conditions are  *
 *  met:                                                                   *
 *                                                                         *
 *     * Redistributions of source code must retain the above copyright    *
 *       notice, this list of conditions and the following disclaimer.     *
 *     * Redistributions in binary form must reproduce the above copyright *
 *       notice, this list of conditions and the following disclaimer in   *
 *       the documentation and/or other materials provided with            *
 *       the distribution.                                                 *
 *     * Neither the name of the author nor the names of its contributors  *
 *       may be used to endorse or promote products derived from this      *
 *       software without specific prior written permission.               *
 *                                                                         *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       *
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   *
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    *
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   *
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    *
 ***************************************************************************/

#include "classtests.h"

ClassTests::ClassTests()
{
    //t_tree();
    //t_field();
    t_pointer();
}

#include "../tree.h"
bool ClassTests::t_tree()
{
    bool t_test = true;
    Tree* tree = new Tree();
    std::vector<int> path = {0, 3, 14, 9, 17};
    std::vector<int> path2 = {0, 3, 66, 6, 6};
    std::vector<int> path3 = {32, 212, 15, 221, 74, 23, 0, 2};

    int win = 1;
    int loss = 0;
    std::cout << "test0";

    tree->addPathRec(path, win);
    tree->addPathRec(path2, loss);
    tree->addPathRec(path3, win);

    if(tree->getBestMove(1) != 32){
        t_test = false;
    }
    std::vector<double> a = tree->getProbabilities(1);
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
    tree->deleteTree(tree);

    return t_test;
}

#include "../field.h"

bool ClassTests::t_field()
{
    bool t_test = true;
    Field a = Field(3,5);
    Field* fieldPointer = new Field(2, 4);
    delete fieldPointer;

}

#include "../savelist.h"
bool ClassTests::t_pointer()
{
    SaveList* saveList;
    t_pointer2(saveList);
    std::cout << "end" << std::endl;
}

bool ClassTests::t_pointer2(SaveList *saveList)
{
    if (!saveList){
        std::cout << "i am function 2" << std::endl;
    }
}


