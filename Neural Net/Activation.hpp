#pragma once
#include "Infos.hpp"
#include <random>

using namespace boost::numeric::ublas;

MATRIXf Activation_Function(const MATRIXf X, float (*funcPtr)(float))
{
	MATRIXf Y;
	for (int line = 0; line <X.size1; line++)
	{
		for (int column = 0; column < X.size2; column++)
		{
			Y.insert_element(line,column,funcPtr(X(line,column)));
		}
	}
	return Y;
}

std::vector<MATRIXf> feedForward(MATRIXf inputM, MATRIXf weightM, MATRIXf biasN)
{
	std::vector<MATRIXf> result;
	result.push_back(prod(weightM,HorizontalConcatenate(inputM,biasN)));
	result.push_back(Activation_Function(result[0], hyperbolicTanActivation));
}
MATRIXf initialiseWeight(int maxW)
{
	MATRIXf weight;
	for (int line = 0; line < weight.size1; line++)
	{
		for (int column = 0; column < weight.size2; column++)
		{
			weight.insert_element(line, column, gen_random_float(maxW));
		}
	}
	
	
}
std::vector<float> evaluateError (MATRIXf input, MATRIXf weight, MATRIXf TargetOutput, MATRIXf TargetClass, MATRIXf bias)
{
	std::vector<float> ERRORS;
	MATRIXf output = feedForward(input,weight,bias)[1];
	MATRIXf Classes = matrix_to_class(output);
	MATRIXf temp = TargetOutput - output;
	carre(temp);
	ERRORS.push_back ((sum_of_all_components(temp) / ((output.size1 * output.size2)*(output.size1 * output.size2))));
	ERRORS.push_back(sum_of_all_components(differentiate(Classes,TargetClass))/samples_counts);
}

MATRIXf backpropagation(MATRIXf input, MATRIXf weight, int eta, MATRIXf bias)
{
	//TODO
	return weight;
}

void train(data_set training_set, data_set validation_set, data_set test_set, int trainingCounts)
{
	MATRIXf WeightMat = initialiseWeight(0.5);
	MATRIXf bias_training, bias_validate, bias_test;
	initialiseMat(bias_training,training_set.inputs.size1 * training_set.inputs.size2,1,1.0);
	initialiseMat(bias_validate, validation_set.inputs.size1 * validation_set.inputs.size2, 1, 1.0);
	initialiseMat(bias_test, test_set.inputs.size1 * test_set.inputs.size2, 1, 1.0);
	std::vector<std::vector<std::vector<float>>> errorsVector; // 1 -> training 2-> validation 3 -> test
	while (trainingCounts)
	{
		WeightMat = backpropagation(training_set.inputs,WeightMat,0.1,bias_training);
		errorsVector.push_back(
		{evaluateError(training_set.inputs, WeightMat, training_set.outputs, training_set.classes, training_set.bias), 
		evaluateError(validation_set.inputs, WeightMat, validation_set.outputs, validation_set.classes, validation_set.bias),
		evaluateError(test_set.inputs, WeightMat, test_set.outputs, test_set.classes, test_set.bias)
		});

	}
}