
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

// OK
Array<Vec2> TestCase0()
{
	return{ Vec2(0, 0), Vec2(100, 0), Vec2(0, 100) };
}

// NG: CCW
Array<Vec2> TestCase1()
{
	return{ Vec2(0, 0), Vec2(0, 100), Vec2(100, 0) };
}

// NG: 0 vertex
Array<Vec2> TestCase2()
{
	return{};
}

// NG: 1 vertex
Array<Vec2> TestCase3()
{
	return{ Vec2(0, 0) };
}

// NG: 2 same points (for 3)
Array<Vec2> TestCase4()
{
	return{ Vec2(0, 0), Vec2(100, 100), Vec2(100, 100) };
}


// NG: 3 same points (for 3)
Array<Vec2> TestCase5()
{
	return{ Vec2(100, 100), Vec2(100, 100), Vec2(100, 100) };
}

// NG: front() == back() (3)
Array<Vec2> TestCase6()
{
	return{ Vec2(0, 0), Vec2(100, 100), Vec2(0, 100), Vec2(0, 0) };
}

// NG: front() == back() (4)
Array<Vec2> TestCase7()
{
	return{ Vec2(0, 0), Vec2(100, 0), Vec2(100, 100), Vec2(0, 100), Vec2(0, 0) };
}

// NG: Self intersection
Array<Vec2> TestCase8()
{
	return{ Vec2(0, 0), Vec2(200, 0), Vec2(0, 100), Vec2(100, 100) };
}

// NG: Spike
Array<Vec2> TestCase9()
{
	return{ Vec2(0, 0), Vec2(100, 0), Vec2(100, 100), Vec2(0, 100), Vec2(0, -100) };
}

// NG: Self intersection
Array<Vec2> TestCase10()
{
	return{ Vec2(0, 0), Vec2(100, 0), Vec2(100, 100), Vec2(200, 100), Vec2(200, 200), Vec2(100, 100), Vec2(0, 100) };
}

// NG: Self intersection
Array<Vec2> TestCase11()
{
	return{ Vec2(0, 0), Vec2(100, 0), Vec2(100, 100), Vec2(200, 100), Vec2(200, 200) };
}

Array<Vec2> TestCase12()
{
	return{ Vec2(0, 0), Vec2(1, 0), Vec2(1, 0), Vec2(100, 0), Vec2(100, 100), Vec2(0, 100) };
}

// NG: 2 same points (for 4)
Array<Vec2> TestCase13()
{
	return{ Vec2(0, 0), Vec2(100, 0), Vec2(100, 0), Vec2(100, 100), Vec2(0, 100) };
}

enum class Terrain
{
	Open, Mountain, River, Ocean
};

void SetTargetFPSOption(size_t index)
{
	constexpr std::array<Optional<double>, 3> options =
	{
		none, 240, 10
	};

	Graphics::SetTargetFrameRateHz(options[index]);
}

void Main()
{
	Window::Resize(800, 720);

	Array<Array<Vec2>> testCases;
	testCases << TestCase0();
	testCases << TestCase1();
	testCases << TestCase2();
	testCases << TestCase3();
	testCases << TestCase4();
	testCases << TestCase5();
	testCases << TestCase6();
	testCases << TestCase7();
	testCases << TestCase8();
	testCases << TestCase9();
	testCases << TestCase10();
	testCases << TestCase11();
	testCases << TestCase12();

	for (auto [i, points] : Indexed(testCases))
	{
		const bool isClockwise = Geometry2D::IsClockwise(points);
		Robust::PolygonValidityFailureType failureType;
		const bool isValid = Robust::Polygon::IsValid(points, failureType);

		Print << U"[{}] {}\nCW={}, IsValid={} ({})"_fmt(i, points, isClockwise, isValid, Robust::ToString(failureType));
	}

	while (System::Update())
	{

	}
}
