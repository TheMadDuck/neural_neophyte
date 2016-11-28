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

#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork()
{
}

NeuralNetwork::NeuralNetwork(int numberInput, int numberHidden, int numberOutput, int numberLayer)
{
    for (int i = 0; i <= numberInput; ++i) {
        _inputNeurons.push_back(0);
        for (int j = 0; j < numberHidden; ++j) {
            _weightInputHidden[i][j] = 0;
        }
    }
    _inputNeurons[numberInput] = -1;


    for (int i = 0; i <= numberHidden; ++i) {  // todo repeat code layer wise...
        _hiddenNeurons.push_back(0);
        for (int j = 0; j < numberOutput; ++j) {
            _weightHiddenOutput[i][j] = 0;
        }
    }
    _hiddenNeurons[numberHidden] = -1;


    for (int i = 0; i < numberOutput; ++i) {
        _outputNeurons.push_back(0);
    }

    initWeights();
}

NeuralNetwork::~NeuralNetwork()
{

}

bool NeuralNetwork::load()
{
    std::cout << "not yet implemented" << std::endl;
}

bool NeuralNetwork::save()
{
    std::cout << "not yet implemented" << std::endl;
}

std::vector<int> NeuralNetwork::discretizeOutput(std::vector<double> pattern)
{
    feedForward(pattern);
    std::vector<int> results;
    for (int i = 0; i < _numberOutput; ++i) {
        results.push_back(marginHandler(_outputNeurons[i]));
    }
    return results;
}

double NeuralNetwork::getAccuracy(std::vector<DataEntry> dataSet) // in ba other pointer construct
{
    double wrongResults = 0;
    int setSize = (int) dataSet.size();
    for (int i = 0; i < setSize; ++i) {
        feedForward(dataSet[i]._pattern);
        bool correctnes = true;
        for (int j = 0; j < _numberOutput; ++j) {
            if(marginHandler(_outputNeurons[j]) != dataSet[i]._target[j]){
                correctnes = false;
            }
        }
        if(!correctnes){
            wrongResults+= 1;
        }
    }
    return 100 - (wrongResults/setSize * 100);
}

void NeuralNetwork::initWeights()
{
    std::cout << "not yet implemented" << std::endl;
}

double NeuralNetwork::activationFunction(double x) // inline?
{
    // return x                 //identity
    // return tanh(x);			// tanH
    // return atan(x);			// arcus tangens
    // return x/1+abs(x);		// Softsign
    // return (sqrt(pow(x,2)+1)-1)/2; // Bend identity
    // return sin(x);			// Sinusoid
    // return exp(pow(-x, 2));  // Gaussian

    return 1/(1+exp(-x));  // sigmoid function
}

void NeuralNetwork::feedForward(std::vector<double> pattern)
{
    // todo for (auto layer : Layers):
    // 			for(int origin = 0; origin < layer.size; ++origin)
    //              ...

    for (int i = 0; i < _numberInput; ++i) {
        _inputNeurons[i] = pattern[i];
    }

    for (int i = 0; i < _numberHidden; ++i) {
        _hiddenNeurons[i] = 0;
        for (int j = 0; j < _numberInput; ++j) {
            _hiddenNeurons[i] += _inputNeurons[j] * _weightInputHidden[j][i];
        }
        _hiddenNeurons[i] = activationFunction(_hiddenNeurons[i]);
    }
    for (int i = 0; i < _numberOutput; ++i) {
        _outputNeurons[i] = 0;
        for (int j = 0; j < _numberHidden; ++j) {
            _outputNeurons[i] += _hiddenNeurons[j] * _weightHiddenOutput[j][i];
        }
        _outputNeurons[i] = activationFunction(_outputNeurons[i]);
    }
}

int NeuralNetwork::marginHandler(double x)
{
    if(x < 0.1){return 0;}
    if(x > 0.9){return 1;}
    return -1;
}

double NeuralNetwork::meanSquareError(std::vector<DataEntry> dataSet)
{
    double mse = 0.0;
    int setSize = dataSet.size();
    for (int i = 0; i < setSize; ++i) {
        feedForward(dataSet[i]._pattern);
        for (int j = 0; j < _numberOutput; ++j) {
            mse += pow((_outputNeurons[j] - dataSet[i]._target[j]), 2);   // todo set shold be a object with pattern/target pair
        }
    }
    return mse/(_numberOutput * setSize);
}

//////////////////////////////////////////////////////////////////
// DataEntry

DataEntry::DataEntry(std::vector<double> p, std::vector<double> t)
    :_pattern(p), _target(t)
{

}
