
# include <Siv3D.hpp> // OpenSiv3D v0.4.0 beta

void Main()
{
	// Set background color to sky blue
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	// Create a new font
	const Font font(60);

	// Create a new texture that contains a cat emoji
	const Texture cat(Emoji(U"🐈"));

	// Coordinates of the cat
	Vec2 catPos(640, 450);

	while (System::Update())
	{
		// Put a message in the middle of the screen
		font(U"Hello, Siv3D!🐣").drawAt(Scene::Center(), Palette::Black);

		// Display the texture with animated size
		cat.resized(100 + Periodic::Sine0_1(1s) * 20).drawAt(catPos);

		// Draw a translucent red circle that follows the mouse cursor
		Circle(Cursor::Pos(), 40).draw(ColorF(1, 0, 0, 0.5));

		// When [A] key is down
		if (KeyA.down())
		{
			// Print `Hello!`
			Print << U"Hello!";
		}

		// When [Move the cat] button is pushed
		if (SimpleGUI::Button(U"Move the cat", Vec2(600, 20)))
		{
			// Move the cat's coordinates to a random position in the screen
			catPos = RandomVec2(Scene::Rect());
		}
	}
}
