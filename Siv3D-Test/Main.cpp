
# include <Siv3D.hpp>

void Main()
{
	const Texture texture(L"example/windmill.png");

	const LineString line
	{
		{ 50, 50 },{ 200, 200 },
		{ 400, 200 },{ 100, 400 },
		{ 500, 400 }
	};

	while (System::Update())
	{
		// 線の幅 8 のスプライン曲線を描く
		line.drawCatmullRom(8.0, Palette::White, true);
	}
}
