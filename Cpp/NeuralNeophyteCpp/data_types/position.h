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

#ifndef POSITION_H
#define POSITION_H
#include <iostream>
#include <vector>


class Position
{
public:
    Position();
    Position(std::vector<int> newVector);
    Position(const Position &newPosition);
    Position(Position &&newPosition);
    Position& operator=(const Position& newPosition);
    Position& operator=(Position&& newPosition);
    int getVectorSize();
    void setVectorSize(int size);
    std::vector<int> getPositionVector() const;
    void setPositionVector(std::vector<int> newPosition);
    int operator [](int i) const {return _positionVector[i];}
    int & operator [](int i) {return _positionVector[i];}
    bool operator ==(const Position& other);
    bool isRandom();
    void setRandomnes(bool random);
    void printPosition();
    void inputPosition();
    int getHash(int base);
private:
    std::vector<int> _positionVector;
    bool _isRandom;
};
/*
template<class T> class positionHash;
template<>
class positionHash<Position>{
public:
    size_t operator()(const Position &p) const{
//        divisor = std::max(_)
        size_t h1 = std::hash<int>()(p.getPositionVector()[0]); // returns only the begin of the position vector
        return h1;
    }
};
*/
#endif // POSITION_H
