#pragma once

#include<map>
#include "Utils.hpp"

using namespace boost::numeric::ublas;

std::vector<std::map<std::string,int>> input_counts;
std::vector<std::map<std::string, int>> outputs_counts;
int samples_counts;

class data_set
{
public:
	data_set(MATRIXf in);
	MATRIXf inputs;
	MATRIXf classes;
	std::vector <int> counts;
	MATRIXf outputs;
	MATRIXf bias;
};

data_set::data_set(MATRIXf in)
{
	inputs=in;
	classes = matrix_to_class(in);
}
