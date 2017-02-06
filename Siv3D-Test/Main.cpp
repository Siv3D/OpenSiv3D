
# include <Siv3D.hpp>

void Main()
{
	Array<float> v;

	for (auto i : step(10000))
	{
		v << 1.0f << 1'000'000.0f;
	}

	Log << v.sum();
	Log << v.sumF();
	Log << v.sum<BigFloat>();

	while (System::Update())
	{

	}
}
