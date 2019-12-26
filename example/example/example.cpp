// example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <assert.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <time.h>
#include <functional>

#include "../../include/ai.h"
#include "../../include/random_tool.h"

int main()
{
	srand(time(NULL));

	size_t layers = 2;
	_STD vector<size_t> layers_neurons = { 3/*network input*/, 3/*first hidden input layer*/, 3 };

	auto weights = _AI generate::random_weights(layers_neurons);

	auto random_inputs = [inputs_counte = layers_neurons[0]]()
	{
		_STD vector<double> inputs(inputs_counte);
		inputs[0] = random_tool::random(0, 100.1); // avg_plays
		inputs[1] = random_tool::random(0, inputs[0]); // wins
		inputs[2] = random_tool::random(0, 1000.1); // fans

		return _STD move(inputs);
	};
	auto inputs = _AI generate::random_inputs(layers_neurons[0], random_inputs);

	// get network prediction for each input row
	auto prediction = _AI neuron_network(inputs, weights);

	_STD cout << "Prediction: sadness, win, happyness\n";

	for (size_t i = 0; i < prediction.size(); i++)
	{
		_STD cout << i << " output: ";
		_STD copy(prediction[i].begin(), prediction[i].end(), _STD ostream_iterator<decltype(prediction)::value_type::value_type>(_STD cout, " "));
		_STD cout << "\n";
	}
	_STD cout << "\n\n";

    return 0;
}

