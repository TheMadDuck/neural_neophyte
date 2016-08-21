#ifndef FIELD_H
#define FIELD_H

#include <vector>

class Field
{
public:
    Field(int height, int width); /*vieleicht noch ne init schreiben?*/
    ~Field(); //destructor
    Field(const Field &other); //copy constructor
    Field(Field&& other); //move constructor
    Field& operator=(const Field& other); //copy assignment
    Field& operator=(Field&& other); //move assignment
    int get(int i, int j);
    void set(int value, int i, int j);
    int getHeight();
    int getWidth();
    int getSizeTotal();
    int getSizeField();
    void showField();
    std::vector<int> flatten();

private:
    std::vector<std::vector<int>> _field;
    int _height;
    int _width;
};



#endif // FIELD_H


