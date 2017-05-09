# include <Siv3D.hpp>

void Main()
{
	// create a new empty texture
	Texture texture;

	while (System::Update())
	{
		// if some files have dropped
		if (DragDrop::HasNewFilePaths())
		{
			// retrieve file paths
			const auto items = DragDrop::GetDroppedFilePaths();

			// load the first file as a Texture
			const Texture tmp(items[0].path);

			// if succeeded
			if (tmp)
			{
				// set the new texture
				texture = tmp;

				// resize the window to be the same size as the texture
				Window::Resize(texture.size());
			}
		}

		// if the texture has content
		if (texture)
		{
			// draw
			texture.draw();
		}
	}
}
