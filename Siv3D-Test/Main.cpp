
# include <Siv3D.hpp>

void Main()
{
	// 線を作成
	const LineString line
	{
		//{600,40},
		{ 50, 100 },{ 600, 100 },
		{ 50, 200 },{ 600, 200 },
		{ 50, 300 },{ 600, 300 },
		{ 50, 400 }//,{600,400}
	};

	int32 index = 0;

	constexpr LineStyle::Parameters styles[5] =
	{
		LineStyle::SquareCap,

		LineStyle::RoundCap,

		LineStyle::NoCap,

		LineStyle::SquareDot,

		LineStyle::RoundDot,
	};

	double dotOffset = 0.0;

	while (System::Update())
	{
		Window::SetTitle(index, L" @ ", Profiler::FPS(), L"FPS");

		if (MouseL.down())
		{
			++index %= 5;
		}


		dotOffset = Cursor::Pos().x / 10.0;

		Line(50, 0, 50, 480).draw();
		Line(600, 0, 600, 480).draw();

		// 黄色い線を太さ 3 で描く
		line.draw(styles[index](dotOffset), 8, Palette::Yellow, MouseR.pressed());

		Line(500, 400, 200, 440).draw(styles[index](dotOffset), 12, Palette::White);
	}
}
