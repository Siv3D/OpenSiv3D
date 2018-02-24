# include <Siv3D.hpp>

void Main()
{
	const Grid<Duration> grid(32, 24, Arg::generator = RNG<Duration>(2.0s, 5.0s));

	while (System::Update())
	{
		for (auto p : step(grid.size()))
		{
			Rect(p * 20, 20).stretched(-2)
				.draw(ColorF(0.3, 0.6, 0.4, Periodic::Sine0_1(grid[p])));
		}
	}
}
