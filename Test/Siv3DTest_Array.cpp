//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "Siv3DTest.hpp"

TEST_CASE("Array::shuffle()")
{
	const Array<int32> v = { 1, 2, 3, 4, 5, 6, 7, 8 , 9, 10 };
	const Array<int32> shuffled = v.shuffled(DefaultRNG{ 123456 });

	const Array<int32> expected = { 4, 10, 1, 8, 5, 7, 2, 9, 3, 6 };
	REQUIRE(shuffled == expected);
}

TEST_CASE("Array::parallel_count_if()")
{
	{
		Array<double> v(8);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = Random();
		}

		REQUIRE(static_cast<size_t>(std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; }))
			== v.parallel_count_if([](double x) { return x < 0.5; }));
	}

	{
		Array<double> v(1024);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = Random();
		}

		REQUIRE(static_cast<size_t>(std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; }))
			== v.parallel_count_if([](double x) { return x < 0.5; }));
	}

	{
		Array<double> v(64 * 1024);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = Random();
		}

		REQUIRE(static_cast<size_t>(std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; }))
			== v.parallel_count_if([](double x) { return x < 0.5; }));
	}

	{
		Array<double> v(1024 * 1024);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = Random();
		}

		REQUIRE(static_cast<size_t>(std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; }))
			== v.parallel_count_if([](double x) { return x < 0.5; }));
	}
}

TEST_CASE("Array::parallel_map()")
{
	{
		Array<uint32> v(64 * 1024);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = RandomUint32();
		}

		REQUIRE(v.map([](uint32 n) { return n / 10.0 + std::sin(n / 10.0) + std::sqrt(n / 10.0); })
			== v.parallel_map([](uint32 n) { return n / 10.0 + std::sin(n / 10.0) + std::sqrt(n / 10.0); }));

	}
}

# if defined(SIV3D_RUN_BENCHMARK)

TEST_CASE("Array::parallel_count_if() : benchmark")
{
	{
		Array<double> v(8);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = Random();
		}

		BENCHMARK("std::count_if() | 8")
		{
			return std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; });
		};

		BENCHMARK("Array::parallel_count_if() | 8")
		{
			return v.parallel_count_if([](double x) { return x < 0.5; });
		};
	}

	{
		Array<double> v(1024);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = Random();
		}

		BENCHMARK("std::count_if() | 1K")
		{
			return std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; });
		};

		BENCHMARK("Array::parallel_count_if() | 1K")
		{
			return v.parallel_count_if([](double x) { return x < 0.5; });
		};
	}

	{
		Array<double> v(64 * 1024);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = Random();
		}

		BENCHMARK("std::count_if() | 64K")
		{
			return std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; });
		};

		BENCHMARK("Array::parallel_count_if() | 64K")
		{
			return v.parallel_count_if([](double x) { return x < 0.5; });
		};
	}

	{
		Array<double> v(1024 * 1024);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = Random();
		}

		REQUIRE(static_cast<size_t>(std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; }))
			== v.parallel_count_if([](double x) { return x < 0.5; }));
	}
}

TEST_CASE("Array::parallel_map() : benchmark")
{
	{
		Array<int32> v(64 * 1024);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = RandomInt32();
		}

		BENCHMARK("Array::map() | 64K")
		{
			return v.map([](int32 n) { return n / 10.0 + std::sin(n / 10.0) + std::sqrt(n / 10.0); });
		};

		BENCHMARK("Array::parallel_map() | 64K")
		{
			return v.parallel_map([](int32 n) { return n / 10.0 + std::sin(n / 10.0) + std::sqrt(n / 10.0); });
		};
	}
}

# endif
