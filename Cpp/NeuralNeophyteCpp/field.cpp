#include "field.h"
#include <iostream>

Field::Field(int height, int width)
    :_height(height), _width(width)
{
    std::cout << "nummer 0" << std::endl;
    _field.resize(height);
    for (int i = 0; i < height; ++i) {
        _field[i].resize(width);
    }
    //std::array<std::array<int, 7>, 7> field;
}

Field::~Field()
{
    //delete _field; Nope, not a pointer.
}

Field::Field(const Field &other){    //Testen!
//    _field(other._field);
//    std::cout << "nummer 1" << std::endl;
    _field = other._field;
    _height = other._height;
    _width = other._width;
}

Field::Field(Field &&other)
    :_field(other._field), _height(other._height), _width(other._width)
{
    std::cout << "nummer 2" << std::endl;
//    other._field = nullptr;
//    other._heigh = NULL;
    //    other._width = NULL;
}

Field &Field::operator=(const Field &other)
{
//    std::vector<std::vector<int>> tempField = other._field;
    std::cout << "nummer 3" << std::endl;
    _field = other._field;
    _height = other._height;
    _width = other._width;
    return *this;
}

Field &Field::operator=(Field &&other)
{
    std::cout << "nummer 4" << std::endl;
    _field = other._field;
    _height = other._height;
    _width = other._width;
    return *this;
}


int Field::get(int i, int j)
{
    return _field[i][j];
}

void Field::set(int value, int i, int j)
{
    _field[i][j] = value;
}

int Field::getHeight()
{
    return _height;
}

int Field::getWidth()
{
    return _width;
}

int Field::getSizeTotal()
{
    return _width*_height;
}

int Field::getSizeField()
{
    return _width *(_height-1);
}

void Field::showField()
{
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            std::cout << _field[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<int> Field::flatten()
{
    /*
    std::vector<int> flatField;
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            flatField.push_back(_field[i][j]);
        }
    }
    */
    //TODO Testen!
    std::vector<int> flatField;
    for (int i = 0; i < _height; ++i) {
        flatField.insert(flatField.end(), _field[i].begin(), _field[i].end());
    }
    return flatField;

}
