#pragma once
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <cmath>
#include <boost/random.hpp>
using namespace boost::numeric::ublas;

typedef matrix <float> MATRIXf;
//#################################################################
//Loads a class to an output matrix or reverse					 ##
//#################################################################
//OUTPUT TO CLASS FUNCTION
// -> Check for every line and every column and takes
//input like 001,100,010 to 1,3,2
//#################################################################
matrix<int> matrix_to_class (matrix<int> binaryM)				
{																
																
	for (int line = 0; line < binaryM.size1; line++)			
	{															
		for (int column = 0; column < binaryM.size2; column++)  
		{														
			if (column)											
			{													
			binaryM.insert_element(line,0,column);				
			}													
		}														
	}															
}																
																
//#################################################################
//CLASS TO OUTPUT FUNCTION	
//-> Check for every line and every column and takes
//input like 1,3,2 to 001,100,010 			
//#################################################################
matrix<int> class_to_matrix (matrix<int> outputM)				
{																
	for (int line = 0; line < outputM.size1; line++)			
	{															
		for (int column = 0; column < outputM.size2; column++)	
		{														
			outputM.insert_element(line, column, 1);			
		}														
	}															
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
ifstream* Load_File(string filePath)
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
template<typename T> void writeFile(string filePath, T Data)
{
	ofstream dataWrite;
	dataWrite.open(filePath);
	if (dataWrite.is_open())
	{
		dataWrite << Data;	
	}
	dataWrite.close();
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
	for (int i = 0; i < TempMat.size1; i++)
	{
		for (int j = 0; j < TempMat.size2; j++)
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
float sum_of_all_components(MATRIXf TempMat)
{
	float total = 0;
	for (int i = 0; i < TempMat.size1; i++)
	{
		for (int j = 0; j < TempMat.size2; j++)
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
MATRIXf HorizontalConcatenate(MATRIXf X, MATRIXf Y)
{
	MATRIXf result;
	int colR = 0;
	for (int line = 0; line <X.size1; line++)
	{
		for (int column = 0; column < X.size2; column++)
		{
			colR++;
			result.insert_element(0, colR, X(line, column));
		}
	}

	for (int line = 0; line <Y.size1; line++)
	{
		for (int column = 0; column < Y.size2; column++)
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
MATRIXf differentiate(MATRIXf X, MATRIXf Y)
{
	MATRIXf result;
	for (int line = 0; line <X.size1; line++)
	{
		for (int column = 0; column < X.size2; column++)
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


float gen_random_float(float max)
{
	float min = 0.0 - max;
	boost::mt19937 rng;
	boost::uniform_real<float> u(min, max);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(rng, u);
	return gen();
}