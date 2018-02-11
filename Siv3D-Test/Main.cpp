# include <Siv3D.hpp>

void Main()
{
	Grid<double> grid(16, 12);

	for (auto& e : grid)
	{
		e = Random(0.4, 1.8);
	}

	while (System::Update())
	{
		for (auto p : step(grid.size()))
		{
			Circle(p * 40, 15).movedBy(20, 20)
				.draw(ColorF(0.0, 1.0, 0.0, Periodic::Sine0_1(1s * grid[p])));
		}
	}
}
