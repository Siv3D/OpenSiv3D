
# include <Siv3D.hpp>

void Main()
{
	Array<double> v;

	for (auto i : step(10000))
	{
		v << 0.1 << 1'000'000;
	}

	Log << v.sum();

	Log << v.sumF(); // Kahan summation
}
