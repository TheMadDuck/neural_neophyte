#include "field.h"
#include <iostream>

Field::Field(int height, int width)
    :_height(height), _width(width)
{
    _field.resize(height);
    for (int i = 0; i < height; ++i) {
        _field[i].resize(width);
    }
    //std::array<std::array<int, 7>, 7> field;
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

int Field::getSize()
{
    return _width*_height;
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
