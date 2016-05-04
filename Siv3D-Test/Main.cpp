
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;

void FunctionA();
void FunctionB();

void Main()
{
	TimeProfiler tp;

	for (int n = 0; n < 100; ++n)
	{
		tp.begin(L"FunctionA");
		
		FunctionA();
		
		tp.end();
	}

	for (int n = 0; n < 100; ++n)
	{
		tp.begin(L"FunctionB");
		
		FunctionB();
		
		tp.end();
	}
}


void FunctionA()
{
	double s = 0.0;
	
	for (auto i : step(1000))
	{
		s += sin(i * 0.001);
	}
	
	volatile double result = s; result;
}

void FunctionB()
{
	double s = 0.0;
	
	for (auto i : step(1000))
	{
		s += sqrt(i * 0.001);
	}
	
	volatile double result = s; result;
}
