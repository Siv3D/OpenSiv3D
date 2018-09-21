
# include <Siv3D.hpp>

void Main()
{
	const FilePath path = U"example/windmill.png";
	const Texture texture(path, TextureDesc::Mipped);

	while (System::Update())
	{
		const Rect rect = texture.draw(40, 40);

		if (rect.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
			rect.draw(ColorF(1.0, 0.5, 0.0, 0.3));
		}

		if (rect.leftClicked())
		{
			Windows::DragDrop::MakeDragDrop(path);
		}
	}
}