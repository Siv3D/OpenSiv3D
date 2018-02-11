# include <Siv3D.hpp>

void Main()
{
	const Font font(40);

	const OutlineGlyph outline = font.getOutlineGlyph(U'T');

	Print << outline.n_contours;
	Print << outline.n_points;

	while (System::Update())
	{
		
	}
}