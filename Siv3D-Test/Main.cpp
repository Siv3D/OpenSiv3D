# include <Siv3D.hpp>

struct Monster
{
	Circle circle;

	ColorF color;

	double direction;

	void update()
	{
		direction += Random(-10_deg, 10_deg);

		circle.moveBy(Circular(Random(0.2, 1.0), direction));
	}

	void draw() const
	{
		circle.draw(color);
	}
};

struct MonsterAdapter
{
	using dataset_type = Array<Monster>;

	using point_type = Vec2;

	using element_type = double;

	static constexpr int32 Dimensions = 2;

	static const element_type* GetPointer(const point_type& point)
	{
		return &point.x;
	}

	static element_type GetElement(const dataset_type& dataset, size_t index, size_t dim)
	{
		return dataset[index].circle.center.elem(dim);
	}

	static element_type DistanceSq(const dataset_type& dataset, size_t index, const element_type* other)
	{
		return dataset[index].circle.center.distanceFromSq(Vec2(other[0], other[1]));
	}
};

void Main()
{
	Window::Resize(1280, 720);

	Array<Monster> monsters(200);

	for (auto& monster : monsters)
	{
		monster.circle.set(RandomVec2(Window::ClientRect()), Random(6, 16));
		
		monster.color = RandomColor();

		monster.direction = Random(360_deg);
	}

	KDTree<MonsterAdapter> kdTree(monsters);

	while (System::Update())
	{
		for (auto& monster : monsters)
		{
			monster.update();
		}

		kdTree.rebuildIndex();

		const Vec2 pos(Cursor::Pos());

		if (MouseL.pressed())
		{
			Circle(pos, 100).drawFrame(2);

			for (const auto index : kdTree.radiusSearch(pos, 100))
			{
				Line(pos, monsters[index].circle.center).draw(6);
			}
		}
		else
		{
			for (const auto index : kdTree.knnSearch(8, pos))
			{
				Line(pos, monsters[index].circle.center).draw(6);
			}
		}

		RenderStateBlock2D blend(BlendState::Additive);

		for (const auto& monster : monsters)
		{
			monster.draw();
		}
	}
}


/*
struct Vec5
{
	std::array<double, 5> elements;
};

struct Vec5Adapter
{
	using dataset_type = Array<Vec5>;

	using point_type = std::array<double, 5>;

	using element_type = double;

	static constexpr int32 Dimension = 5;

	static const element_type* GetPointer(const point_type& point)
	{
		return point.data();
	}

	static element_type GetElement(const dataset_type& dataset, size_t index, int32 dim)
	{
		return dataset[index].elements[dim];
	}

	static element_type Distance(const dataset_type& dataset, size_t index, const element_type* other)
	{
		const double d0 = dataset[index].elements[0] - other[0];
		const double d1 = dataset[index].elements[1] - other[1];
		const double d2 = dataset[index].elements[2] - other[2];
		const double d3 = dataset[index].elements[3] - other[3];
		const double d4 = dataset[index].elements[4] - other[4];
		return d0 * d0 + d1 * d1 + d2 * d2 + d3 * d3 + d4 * d4;
	}
};

*/

	/*
	Array<Vec5> monsters(200);

	for (auto& monster : monsters)
	{
		const Vec2 v = RandomVec2(Window::ClientRect());
		monster.elements[0] = v.x;
		monster.elements[1] = v.y;
		monster.elements[2] = 0;
		monster.elements[3] = 0;
		monster.elements[4] = 0;
	}

	KDTree<Vec5Adapter> kdTree(monsters);

	while (System::Update())
	{
		const Vec2 pos(Cursor::Pos());
		const std::array<double, 5> posF = { pos.x, pos.y, 0,0,0 };

		if (MouseL.pressed())
		{
			Circle(pos, 80).drawFrame(1);

			for (const auto index : kdTree.radiusSearch(posF, 80))
			{
				Line(pos, Vec2(monsters[index].elements[0], monsters[index].elements[1])).draw(6, Palette::White);
			}
		}
		else
		{
			for (const auto index : kdTree.knnSearch(8, posF))
			{
				Line(pos, Vec2(monsters[index].elements[0], monsters[index].elements[1])).draw(6, Palette::White);
			}
		}

		for (const auto& monster : monsters)
		{
			Circle(monster.elements[0], monster.elements[1], 5).draw();
		}
	}
	//*/