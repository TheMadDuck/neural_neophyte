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

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <iostream>
#include <vector>
#include <math.h>
#include "layer.h"

class DataEntry; // forward declaration

class NeuralNetwork
{
    friend class Learn; // Realy??
public:
    NeuralNetwork();
    NeuralNetwork(std::vector<std::vector<int>> networkForm); // network form := [0][0] first layers type, [0][1] first layers size, [1][0] second layers type,...
    ~NeuralNetwork();

    bool load();
    bool save();
    std::vector<int> discretizeOutput(std::vector<double> pattern);
    double getAccuracy(std::vector<DataEntry> dataSet); // do not use int
    int getNumberLayer();
    std::vector<std::vector<int> > getForm();
    Layer *getOutput();

private:
    void initWeights();
    double activationFunction(double x);
    void feedForward(std::vector<double> pattern);
    int marginHandler(double x);
    double meanSquareError(std::vector<DataEntry> dataSet);

    //Todo include _networkForm (instead of the _number... variables)
    std::vector<std::vector<int>> _networkForm;
    //int _numberLayer; should be used ?!

    std::vector<Layer*> _network;  // layer Pointer???
    //Layer _inputNeurons;  // test Layer (=) std::vector<double>
    //Layer _hiddenNeurons;
    //Layer _outputNeurons;

    std::vector<std::vector<std::vector<double>>> _edgeWeights; // performance?
//    std::vector<std::vector<double>> _weightInputHidden;
//    std::vector<std::vector<double>> _weightHiddenOutput;
};

class DataEntry  // necassary? use dataset from savelist?! (just a prototype)
{
public:
    DataEntry(std::vector<double> p, std::vector<double> t);
    std::vector<double> _pattern;
    std::vector<double> _target;
};

#endif // NEURALNETWORK_H
