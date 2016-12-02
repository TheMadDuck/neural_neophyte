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
#include <random>

NeuralNetwork::NeuralNetwork()
{
}

NeuralNetwork::NeuralNetwork(std::vector<std::vector<int> > networkForm)
{
    /*
    for(std::vector<int> layerForm: networkForm){
        Layer* layer = new Layer(layerForm[0], layerForm[1]);
        for (int i = 0; i < layerForm[1]; ++i) {
            //for (int j = 0; j < layerForm2; ++j) {
                // init edgeWeights.
            //}

        }
        _network.push_back(layer);
    }
    */
    for (int numberLayer = 0; numberLayer < networkForm.size(); ++numberLayer) {
        Layer* layer = new Layer(networkForm[numberLayer][0],  // init layer type
                                 networkForm[numberLayer][1]); // init layer size
        _network.push_back(layer);
        if(numberLayer != 0){
            for (int i = 0; i < networkForm[numberLayer-1][1]; ++i) {
                for (int j = 0; j < networkForm[numberLayer][1]; ++j) {
                    _edgeWeights[numberLayer-1][i][j]= 0;
                }
            }
        }
    }
    /*
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
    */

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
    Layer* outputNeurons = _network.back();
    int numberOutput = _networkForm.back()[1];
    for (int i = 0; i < numberOutput; ++i) {
        //results.push_back(marginHandler(_outputNeurons[i]));
        //double test = outputNeurons->get(i); // why does [i] not work??
        results.push_back(marginHandler(outputNeurons->get(i)));
    }
    return results;
}

double NeuralNetwork::getAccuracy(std::vector<DataEntry> dataSet) // in ba other pointer construct
{
    double wrongResults = 0;
    int setSize = (int) dataSet.size();
    Layer* outputNeurons = _network.back();
    int numberOutput = _networkForm.back()[1];
    for (int i = 0; i < setSize; ++i) {
        feedForward(dataSet[i]._pattern);
        bool correctnes = true;
        for (int j = 0; j < numberOutput; ++j) {
            //if(marginHandler(_outputNeurons[j]) != dataSet[i]._target[j]){
            if(marginHandler(outputNeurons->get(j)) != dataSet[i]._target[j]){
                correctnes = false;
            }
        }
        if(!correctnes){
            wrongResults+= 1;
        }
    }
    return 100 - (wrongResults/setSize * 100);
}

int NeuralNetwork::getNumberLayer()
{
    return _network.size();
}

std::vector<std::vector<int> > NeuralNetwork::getForm()
{
    return _networkForm;
}

Layer* NeuralNetwork::getOutput()
{
    return _network.back();
}

void NeuralNetwork::initWeights()
{
    int numberInput = _networkForm.back()[1];
    int numberHidden = _networkForm.back()[1];
    double rangeHidden = 1/(double) sqrt(numberInput); //(double) necessary?
    double rangeOutput = 1/(double) sqrt(numberHidden); //(double) necessary?
    for (int i = 0; i < numberInput; ++i) {
        for (int j = 0; j < numberHidden; ++j) {
            // range von -rangeHidden bis +rangeHidden
        }
    }
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

    for (int numberLayer = 0; numberLayer < _network.size(); ++numberLayer) {
        for (int i = 0; i < _network[numberLayer]->getSize(); ++i) {
            if(_network[numberLayer]->type() == 1){
                _network[numberLayer][i] = pattern[i];
            }
            else{
                /*
                _network[numberLayer][i] = 0; // can we just use a help variable here? ( int sum = 0)
                for (int j = 0; j < _network[numberLayer-1]->getSize(); ++j) {
                    _network[numberLayer][i] += _network[numberLayer-1]->get(j) *_edgeWeights[numberLayer-1][j][i]; // TEST!
                }
                _network[numberLayer][i] = activationFunction(_network[numberLayer]->get(i));
                */
                double sum = 0; // can we just use a help variable here? ( int sum = 0)
                for (int j = 0; j < _network[numberLayer-1]->getSize(); ++j) {
                    sum += _network[numberLayer-1]->get(j) *_edgeWeights[numberLayer-1][j][i]; // TEST!
                }
                _network[numberLayer][i] = activationFunction(sum);

            }
        }
    }


    /*
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
    */
}

int NeuralNetwork::marginHandler(double x)
{
    if(x < 0.1){return 0;}
    if(x > 0.9){return 1;}
    return -1;
}

double NeuralNetwork::meanSquareError(std::vector<DataEntry> dataSet)
{
    int numberOutput = _networkForm.back()[1];
    double mse = 0.0;
    int setSize = dataSet.size();
    Layer* outputNeurons = _network.back();
    for (int i = 0; i < setSize; ++i) {
        feedForward(dataSet[i]._pattern);
        for (int j = 0; j < numberOutput; ++j) {
            //mse += pow((_outputNeurons[j] - dataSet[i]._target[j]), 2);   // todo set shold be a object with pattern/target pair
            mse += pow((outputNeurons->get(j) - dataSet[i]._target[j]), 2);   // todo set shold be a object with pattern/target pair
        }
    }
    return mse/(numberOutput * setSize);
}

//////////////////////////////////////////////////////////////////
// DataEntry

DataEntry::DataEntry(std::vector<double> p, std::vector<double> t)
    :_pattern(p), _target(t)
{

}
