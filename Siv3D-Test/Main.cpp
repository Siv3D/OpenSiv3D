# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(Color(250, 240, 230));

	const Font font(20, Typeface::Bold, FontStyle::Italic);

	while (System::Update())
	{
		font(L"絵文字🐣🗻🙈👌の表示に対応").draw(20, 20, Palette::Brown);
	}
}
