#pragma once

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <cmath>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/random.hpp>
#include <boost/lexical_cast.hpp>

#define D_SCL_SECURE_NO_WARNINGS 1
#define PLOT_DEBUG 1

using namespace boost::numeric::ublas;
typedef matrix <float, row_major, unbounded_array<float>> MATRIXf;

//#################################################################
//Loads a class to an output matrix or reverse					 ##
//#################################################################
//OUTPUT TO CLASS FUNCTION
// -> Check for every line and every column and takes
//input like 001,100,010 to 1,3,2
//#################################################################
MATRIXf matrix_to_class (const MATRIXf inputM)
{	
	MATRIXf output;
	for (std::size_t line = 0; line < inputM.size1(); line++)
	{															
		for (std::size_t column = 0; column < inputM.size2(); column++)
		{														
			if (column == 1)											
			{													
				output.insert_element(line,0.0,column);
			}													
		}														
	}
	
	return output; 
}																															
//#################################################################
//CLASS TO OUTPUT FUNCTION	
//-> Check for every line and every column and takes
//input like 1,3,2 to 001,100,010 			
//#################################################################
MATRIXf class_to_matrix (const MATRIXf inputM)
{		
	MATRIXf output;
	for (std::size_t line = 0; line < inputM.size1(); line++)
	{															
		for (std::size_t column = 0; column < inputM.size2(); column++)
		{														
			output.insert_element(line, column, 1);
		}														
	}	
	return output;
}								
//#################################################################

//#################################################################
//Loads a file, write a file or saves one    					 ##
//#################################################################

#include <fstream>
using namespace std;

//#################################################################
//LOAD FILE TO MEMORY
// -> Check for every line and loads it in memory for later usage
// -> Returns a pointer to loaded file
//#################################################################
ifstream* Load_File(const string filePath)
{
	ifstream dataFile (filePath , ios::in);
	if (dataFile.is_open())
	{ 
		return &dataFile;
	}
	return NULL;
}
//#################################################################
//WRITE FILE 
// -> Takes input path 
// -> Writes DATA to filePath
//#################################################################
template<typename T> void writeFile(const string filePath, T Data)
{
	ofstream dataWrite;
	dataWrite.open(filePath);
	if (dataWrite.is_open())
	{
		for (auto i : Data)
		{
			dataWrite << i;
		}
	}
	dataWrite.close();
}
void WritePlotValues(std::vector<std::vector<std::vector<float>>> errorsVector)
{
	ofstream dataWrite;
	for (int h = 0; h <=2 ; h++)
	{
		for (int j = 0; j <= 1; j++)
		{
			writeFile(to_string(h) + "SetE" + to_string(j) + ".dat", errorsVector[h][j]);
		}
	}

}
//#################################################################
//#################################################################

//#################################################################
//Multiple operation on Matrices            					 ##
//#################################################################

//#################################################################
//POWER 2 MATRICES 
// -> Takes input matrix 
// -> Powers by two
//#################################################################
void carre(MATRIXf &TempMat)
{
	for (unsigned i = 0; i < TempMat.size1(); i++)
	{
		for (unsigned j = 0; j < TempMat.size2(); j++)
		{
			TempMat(i, j) = std::pow(TempMat(i, j), 2.0);
		}
	}
}

//#################################################################
//SUM OF ALL COMPONENTS
// -> Takes input matrix 
// -> Adds all components to a single float
//#################################################################
float sum_of_all_components(const MATRIXf TempMat)
{
	float total = 0;
	for (unsigned i = 0; i < TempMat.size1(); i++)
	{
		for (unsigned j = 0; j < TempMat.size2(); j++)
		{
			total += TempMat(i, j);
		}
	}

	return total;
}
//#################################################################
//CONCATENATE HORIZONTALLY
// -> Takes 2 input matrix 
// -> Concatenates them like : {1,3,2,5,6,1,3,6,4,2,6}
//#################################################################
MATRIXf HorizontalConcatenate(const MATRIXf X, const MATRIXf Y)
{
	MATRIXf result;
	int colR = 0;
	for (unsigned line = 0; line <X.size1(); line++)
	{
		for (unsigned column = 0; column < X.size2(); column++)
		{
			colR++;
			result.insert_element(0, colR, X(line, column));
		}
	}

	for (unsigned line = 0; line <Y.size1(); line++)
	{
		for (unsigned column = 0; column < Y.size2(); column++)
		{
			colR++;
			result.insert_element(0, colR, Y(line, column));
		}
	}
	return result;
}
//#################################################################
// != 2 MATRICES 
// -> Takes 2 input matrix 
// -> Calculates all the differencies
//#################################################################
MATRIXf differentiate(const MATRIXf X, const MATRIXf Y)
{
	MATRIXf result;
	for (unsigned line = 0; line <X.size1(); line++)
	{
		for (unsigned column = 0; column < X.size2(); column++)
		{
			if (X(line, column) == Y(line, column))
			{
				result.insert_element(line, column, 1.0);
			}
		}
	}
	return result;
}
//#################################################################
//HYPERBOLYC TANGANT  
// -> Calculates tanh or deriv(tanh)
//#################################################################
float hyperbolicTanActivation(const float X)
{
	float tempX = 0;
	tempX = X;
	tempX = std::tanh(tempX) + 1.0;
	tempX = tempX / 2.0;
	return tempX;
}
float DerivativehyperbolicTanActivation(const float X)
{
	float tempX = 0;
	tempX = X;
	tempX = 1 - std::pow(std::tanh(tempX), 2.0);
	tempX = tempX / 2.0;
	return tempX;
}

//#################################################################
//RANDOM NUMBER  
// -> Generate a random float from -max to max
//#################################################################
float gen_random_float(float max)
{
	float min = 0.0 - max;
	boost::mt19937 rng;
	boost::uniform_real<float> u(min, max);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(rng, u);
	return gen();
}

//#################################################################
//INITIALISE A MATRIX  
// -> Initialise a Matrix of size size1/size2 and filled with value
//#################################################################
void initialiseMat(MATRIXf &MAT, const int size1, const int size2, const float value)
{
	for (unsigned size1 = 0; size1 <MAT.size1(); size1++)
	{
		for (unsigned size2 = 0; size2 < MAT.size2(); size2++)
		{
			MAT.insert_element(size1,size2,value);
		}
	}
}
//#################################################################
//#################################################################