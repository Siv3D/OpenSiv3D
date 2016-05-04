
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;
using namespace s3d::literals;
using namespace std::chrono_literals;

int ga, gb;
void FunctionA();
void FunctionB();

void Main()
{
	TimeProfiler tp;

	for (int n = 0; n < 1000; ++n)
	{
		tp.begin(L"FunctionA");
		
		FunctionA();
		
		tp.end();
	}

	for (int n = 0; n < 1000; ++n)
	{
		tp.begin(L"FunctionB");
		
		FunctionB();
		
		tp.end();
	}

	Log(ga, L'\n', gb);
}


void FunctionA()
{
	int32 a = Range(0, 1000000).reduce1(std::plus<>());

	ga = a;
}

void FunctionB()
{
	int32 a = 0;

	for (int i = 0; i <= 1000000; ++i)
	{
		a += i;
	}

	gb = a;
}
