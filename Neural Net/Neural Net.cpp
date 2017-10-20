// Neural Net.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Activation.hpp"


using namespace boost;

std::vector<MATRIXf> initialise(std::string Dir)
{
	MATRIXf DMat,CMAt;
	unsigned lines = 0;
	boost::scoped_ptr<ifstream> inputDir (new ifstream (Load_File(Dir)));
	float data1,data2,data3,data4, Class1,Class2,Class3;
	while (*inputDir >> data1 >> data2 >> data3 >> data4 >> Class1 >> Class2 >> Class3)
	{
		DMat.insert_element(lines,0,data1);
		DMat.insert_element(lines, 1, data2);
		DMat.insert_element(lines, 2, data3);
		DMat.insert_element(lines, 3, data4);


		CMAt.insert_element(lines, 0, Class1);
		CMAt.insert_element(lines, 1, Class2);
		CMAt.insert_element(lines, 2, Class3);

		++lines;
	}
	input_counts.push_back(lines);
	std::vector<MATRIXf> reult = {CMAt, DMat};
	return reult;
}
int main(int argc, char *argv[])
{

	std::vector<MATRIXf> TempVec = initialise("iris_training");
	data_set Training (TempVec[0], TempVec[1]);
	
	TempVec = initialise("iris_test");
	data_set Test(TempVec[0], TempVec[1]);

	TempVec = initialise("iris_validation");
	data_set Validation(TempVec[0], TempVec[1]);
	train(Training, Validation, Test, 500);
	std::system("python Plot.py");

	
	return 0;
}
