#pragma once

#include <vector>
#include <assert.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>

#include "linal.h"
#include "random_tool.h"

#if defined(__cplusplus)
#define _AI_BEGIN	namespace ai {
#define _AI_END		}
#define _AI ::ai::
#endif

_AI_BEGIN
	// returns vector of predictions, that's network execute result.
	template<typename IterT, typename elementT>
	static _STD vector<double> neuron_network(IterT begin, IterT end, _LINAL matrix<elementT> const &weights)
	{
		return _LINAL scalar::vect_x_mtx(begin, end, weights);
	}

	// get network prediction for each input row
	// returns matrix where each row is network execute result(prediction).
	template<typename elementT>
	static _LINAL matrix<double> neuron_network(_LINAL matrix<elementT> const &input, _LINAL matrix<elementT> const &weights)
	{
		assert(input.size() == weights.size());

		_LINAL matrix<double> output;
		output.reserve(input.size());

		for (size_t row(0); row < input.size(); ++row)
			output.emplace_back(_AI neuron_network(input[row].begin(), input[row].end(), weights));

		return _STD move(output);
	}

	// If network has hidden layers(layersWeights contaions weghts for each layer)
	// get network prediction for each input row
	// returns matrix where each row is network execute result(prediction).
	template<typename elementT>
	static _LINAL matrix<elementT> neuron_network(_LINAL matrix<elementT> const &input, _STD vector< _LINAL matrix<elementT> > const &layersWeights)
	{
		_LINAL matrix<elementT> layerInput = input;
		for (auto const &layerWeight : layersWeights)
			layerInput = _AI neuron_network(layerInput, layerWeight);

		return _STD move(layerInput);
	}

	namespace generate
	{
		// example of layers_neurons = { 3/*network input*/, 3/*first hidden input layer*/, 3 };
		static _STD vector< _LINAL matrix<double> > random_weights(_STD vector<size_t> const &layers_neurons)
		{
			// code below randoms weights to smth like this:
			//_STD vector< _LINAL matrix<double> > weights =
			//{
			//	{// hidden layer 0, aliace hid
			//  avg_plays, wins, fans
			//		{ 0.1, -0.2, .0 }, // hid[0]
			//		{ 0.3, -0.3, .0 }, // hid[1]
			//		{ 0.5, -0.1, .0 }  // hid[2]
			//	},
			//	{// out layer
			//	 //hid[0], hid[1], hid[2]
			//		{ 0.1,   -0.2, .0 }, // sadness?
			//		{ 0.3,   -0.3, .0 }, // win?
			//		{ 0.5,   -0.1, .0 }  // happyness?
			//	},
			//};
			_STD vector< _LINAL matrix<double> > weights;
			for (size_t i = 1; i < layers_neurons.size(); i++)
			{
				_LINAL matrix<double> layerNeurons(layers_neurons[i]);
				_STD generate(layerNeurons.begin(), layerNeurons.end(), [i, &layers_neurons]()
				{
					// количество инпутов нейрона на текущем уровне равно количеству аутпутов на предыдущем
					_STD vector<double> neuronInput(layers_neurons[i - 1]);

					_STD generate(neuronInput.begin(), neuronInput.end(), []() { return random_tool::random(-3.3, 1.1); });
					return _STD move(neuronInput);
				});

				weights.emplace_back(_STD move(layerNeurons));
			}

			return _STD move(weights);
		}

		static _LINAL matrix<double> random_inputs(size_t inputsCount, _STD function<_STD vector<double>()> randomFunction)
		{
			// code below randoms inputs to smth like this:
			// we will make neuron network execute for each row(here is 3 executes)
			//LINAL matrix<double> inputs(layers_neurons[0]) =
			//{
			//	{// Input for hidden layer
			// avg_plays, wins, fans
			//		{ 3,   3.4, 5.6 }, first execute
			//		{ 0,     2, 1 }, second execute
			//		{ 1.3, 5.3, 4.3 } third execute
			//	},
			//	{// Input for output layer
			//		{ 4,   3.4, 6 }, 
			//		{ 1,     3, -1 }, 
			//		{ 1.3, 1.3, 1.3 }
			//	}
			//}

			_LINAL matrix<double> inputs;
			for (size_t i(0); i < inputsCount; ++i)
				inputs.emplace_back(randomFunction());
			return _STD move(inputs);
		}
	}
_AI_END