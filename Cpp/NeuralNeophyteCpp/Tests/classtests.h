#ifndef CLASSTESTS_H
#define CLASSTESTS_H
#include<iostream>
#include <vector>
#include "../savelist.h"

class ClassTests
{
public:
    ClassTests();
    bool t_tree();
    bool t_field();
    bool t_pointer();
    bool t_pointer2(SaveList* saveList = nullptr);
};

#endif // CLASSTESTS_H
