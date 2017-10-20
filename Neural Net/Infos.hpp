#pragma once

#include<map>
#include "Utils.hpp"

using namespace boost::numeric::ublas;

static std::vector<int> input_counts;
static std::vector<int> outputs_counts;
int samples_counts;

class data_set
{
public:
	data_set(MATRIXf in, MATRIXf classes);
	MATRIXf inputs;
	MATRIXf classes;
	std::vector <int> counts;
	MATRIXf outputs;
	MATRIXf bias;
};

data_set::data_set(MATRIXf in, MATRIXf classes)
{
	inputs=in;
	classes = classes;
}
