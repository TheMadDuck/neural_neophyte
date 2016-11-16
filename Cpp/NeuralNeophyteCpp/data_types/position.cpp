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

#include "position.h"

Position::Position()
{
    _isRandom = true;
}

Position::Position(std::vector<int> newVector)
    :_positionVector(newVector)
{
}

Position::Position(const Position &newPosition)
{
    _positionVector = newPosition._positionVector;
}

Position::Position(Position &&newPosition)
{
    _positionVector = newPosition._positionVector;
}

Position &Position::operator=(const Position &newPosition)
{
    _positionVector = newPosition._positionVector;
    return *this;
}

Position &Position::operator=(Position &&newPosition)
{
    _positionVector = newPosition._positionVector;
    return *this;
}

int Position::getVectorSize()
{
    return _positionVector.size();
}

void Position::setVectorSize(int size)
{
    for (int i = 0; i < size; ++i) {
        _positionVector.push_back(0);
    }
}

std::vector<int> Position::getPositionVector() const
{
    return _positionVector;
}

void Position::setPositionVector(std::vector<int> newPosition)
{
    _positionVector = newPosition;
}

bool Position::operator ==(const Position &other)
{
    /*
    if(_positionVector == other.getPositionVector()){
        return true;
    }
    else{
        return false;
    }
    */
    return (_positionVector == other.getPositionVector());
}

bool Position::isRandom()
{
    return _isRandom;
}

void Position::setRandomnes(bool random)
{
    _isRandom = random;
}

void Position::printPosition()
{
    for(int i: _positionVector){
        std::cout << i << " ";
    }
}

void Position::inputPosition()
{
    for(int i = 0; i<getVectorSize(); i++){
        std::cin >> _positionVector[i];
    }
}
