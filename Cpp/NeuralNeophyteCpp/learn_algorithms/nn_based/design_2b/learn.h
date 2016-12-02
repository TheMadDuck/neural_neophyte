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

#ifndef LEARN_H
#define LEARN_H

#include <vector>
#include "neuralnetwork.h"

class Learn
{
    friend class NeuralNetwork; //realy???
public:
    Learn(NeuralNetwork nn,
          double learningRate = 0.2,
          double momentum = 0.2,
          int maxEpochs = 100,
          double desiredAccuracy = 0.7,
          bool batch = false,
          double trainAccuracy = 0,
          double validateAccuracy = 0,
          double trainMSE = 0,
          double validateMSE = 0);
    void setLearningRate(double learningRate);
    void setMomentum(double momentum);
    void setDesiredAccuracy(double desiredAccuracy);
    void setMaxEpochs(int maxEpochs);
    void setBatchMode(bool batch);
    void learn();

private:
    double getErrorGradient(int layer, double desiredValue, double ouputValue);
    void runEpoch(std::vector<DataEntry> trainingSet); // do not use int
    void backpropagation(std::vector<double> desiredOutputs); // double pointer?
    void updateWeights();


    NeuralNetwork _nn;
    std::vector<std::vector<std::vector<double>>> _deltaWeights;
    std::vector<std::vector<double>> _errorGradients;

    double _learningRate;
    double _momentum;
    int _epoch; // maybe long?
    int _maxEpochs;
    double _desiredAccuracy;
    bool _batchLearning;

    double _trainAccuracy;
    double _validationAccuracy; //needed?
    double _trainMSE;
    double _validationMSE;



};

#endif // LEARN_H
