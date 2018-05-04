
# include <Siv3D.hpp>

void Main()
{
	constexpr size_t N = 100'000'000;

	DefaultRNGType sfmt;
	Xorshift1024StarPhi phi;
	Xorshift128Plus plus;
	Xoroshiro128Plus oshiro;
	uint64 a = 0;

	for (auto n : step(4))
	{
		{
			MicrosecClock m;

			for (size_t i = 0; i < N; ++i)
			{
				a += sfmt();
			}

			m.print();
		}

		{
			MicrosecClock m;

			for (size_t i = 0; i < N; ++i)
			{
				a += phi();
			}

			m.print();
		}

		{
			MicrosecClock m;

			for (size_t i = 0; i < N; ++i)
			{
				a += plus();
			}

			m.print();
		}

		{
			MicrosecClock m;

			for (size_t i = 0; i < N; ++i)
			{
				a += oshiro();
			}

			m.print();
		}

		Print << U"----";
	}

	Print << sfmt();
	Print << phi();
	Print << plus();
	Print << oshiro();
	Print << a;

	while (System::Update())
	{

	}
}
