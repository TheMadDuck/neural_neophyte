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

#include "learn.h"

Learn::Learn(NeuralNetwork nn,
             double learningRate,
             double momentum,
             int maxEpochs,
             double desiredAccuracy,
             bool batch,
             double trainAccuracy,
             double validateAccuracy,
             double trainMSE,
             double validateMSE)
    :_nn(nn),
      _learningRate(learningRate),
      _momentum(momentum),
      _maxEpochs(maxEpochs),
      _desiredAccuracy(desiredAccuracy),
      _batchLearning(batch),
      _trainingAccuracy(trainAccuracy),
      _validationAccuracy(validateAccuracy),
      _trainingMSE(trainMSE),
      _validationMSE(validateMSE)
{
    for (int layer = 1; layer < nn.getNumberLayer(); ++layer) {
//		_deltaWeights[layer];
        for (int i = 0; i <= nn.getForm()[layer-1][1]; ++i) {  // note the >= ! (be careful with >= and > i the whole class
            for (int j = 0; j < nn.getForm()[layer][1]; ++j) {
                _deltaWeights[layer][i][j] = 0;
            }
        }
    }
    for (int layer = 1; layer < nn.getNumberLayer(); ++layer) {
        for (int i = 0; i <= nn.getForm()[layer][1]; ++i) {
            _errorGradients[layer-1][i]= 0; // -1 to save space
        }
    }
}

void Learn::setLearningRate(double learningRate)
{
    _learningRate = learningRate;
}

void Learn::setMomentum(double momentum)
{
    _momentum = momentum;
}

void Learn::setDesiredAccuracy(double desiredAccuracy)
{
    _desiredAccuracy = desiredAccuracy;
}

void Learn::setMaxEpochs(int maxEpochs)
{
    _maxEpochs = maxEpochs;
}

void Learn::setBatchMode(bool batch)
{
    _batchLearning = batch;
}

void Learn::learn()
{

}

double Learn::getErrorGradient(int layer, double desiredValue, double ouputValue)
{

}

void Learn::runEpoch(std::vector<int> trainingSet)
{

}

void Learn::backpropagation(std::vector<double> desiredOutputs) // not use member-variable?
{
    for (int layer = _nn.getNumberLayer()-1; layer >= 1; --layer) {
        for (int i = 0; i < _nn.getForm()[layer][1]; ++i) {
            _errorGradients[layer][i] = getErrorGradient(layer, desiredOutputs[i], _nn.getOutput()->get(i));
            for (int j = 0; j < _nn.getForm()[layer-1][1]; ++j) {
                if(!_batchLearning){
                    std::cout << "not yet implemented" << std::endl;
                    _deltaWeights[layer-1][j][i] = _learningRate;// * _nn[layer][j];
                }
            }
        }
    }
}

void Learn::updateWeights()
{
    for (int layer = 0; layer < _nn.getNumberLayer()-1; ++layer) {
        for (int i = 0; i <= _nn.getForm()[layer][1]; ++i) {
            for (int j = 0; j < _nn.getForm()[layer+1][1]; ++j) {
                _nn._edgeWeights[layer][i][j] += _deltaWeights[layer][i][j];  // can wirte on edgeweights because neuralnetwork is a friend class. realy a good solution???
                if(_batchLearning){
                    _deltaWeights[layer][i][j] = 0;
                }
            }
        }
    }
}
