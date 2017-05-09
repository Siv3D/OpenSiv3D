# include <Siv3D.hpp>

void Main()
{
	// 空のテクスチャ
	Texture texture;

	while (System::Update())
	{
		// 何かがドロップされた
		if (DragDrop::HasNewFilePaths())
		{
			const auto items = DragDrop::GetDroppedFilePaths();

			// テクスチャとしてロードに成功したら
			if (const Texture tmp{ items[0].path })
			{
				// テクスチャを置き換える
				texture = tmp;

				Log << texture.size();

				// ウィンドウをテクスチャと同じサイズにする
				Window::Resize(texture.size(), false);
			}
		}

		if (texture)
		{
			texture.draw();
		}
	}
}