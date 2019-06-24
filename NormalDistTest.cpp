/*
 * NormalDistTest.cpp
 *  Created on: Jun 19, 2019
 *      Author: Kalebin
 */

/*
 * This file is used to test the normal distributions
 */
/*
#include <iostream>
#include <random>
#include <cmath>
#include <chrono>
*/
//void testFunc();

/*
int main()
{
	for (int i = 0; i < 10; i++)
	{
		std::cout << i << std::endl;
		testFunc();
	}
	*/
	/*
	double num = 0;
	std::vector <double> badnums;
	for (int i = 0 ; i < 1000; i++)
	{
		num = nDist(generator);
		if (fabs(num) > 3*(0.01*0.01))
		{
			//std::cout << "\t" << num << " is bad." << std::endl;
			badnums.push_back(num);
		}
		else
		{
			//std::cout << num << std::endl;
		}
	}
	std::cout << badnums.size()/1000000 << "% are bad numbers" << std::endl;
	*/
//}
/*
void testFunc()
{
	static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	srand(seed);
	seed = rand();
	std::default_random_engine generator (seed);

	double stdev; // standard deviation;
	double mu; // expectation value

	stdev = 0.01;
	mu = 0;
	//std::default_random_engine generator;
	std::normal_distribution<double> nDist(mu, stdev*stdev);

	double num1;
	double num2;
	for (int i = 0; i < 10; i++)
	{
		num1 = nDist(generator);
		for (int j = 0; j < 10; j++)
		{
			num2 = nDist(generator);
			std::cout << "\tnum1 = " << num1 << "\tnum2 = " << num2 << std::endl;
		}
	}
}
*/
