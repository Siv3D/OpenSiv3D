
void Main()
{
	// Set background color to sky blue
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	// Create a new font
	const Font font(60);

	// Create a new emoji font
	const Font emojiFont(60, Typeface::ColorEmoji);

	// Set emojiFont as a fallback
	font.addFallback(emojiFont);

	// Create a texture from an image file
	Texture texture("example/windmill.png");

	// Create a texture from an emoji
	Texture emoji(_emoji("🐈"));

	// Coordinates of the emoji
	Vec2 emojiPos(300, 150);

	// Print a text
	Print << "Push [A] key";

	while (System::Update())
	{
		// Draw a texture
		texture.draw(200, 200);

		// Put a text in the middle of the screen
		font("Hello, Siv3D!🚀").drawAt(Scene::Center(), Palette::Black);

		// Draw a texture with animated size
		emoji.resized(100 + Periodic::Sine0_1(_s(1)) * 20).drawAt(emojiPos);

		// Draw a red transparent circle that follows the mouse cursor
		Circle(Cursor::Pos(), 40).draw(ColorF(1, 0, 0, 0.5));

		// When [A] key is down
		if (KeyA.down())
		{
			// Print a text message
			Print << "Hello!";
		}

		// When [Button] is pushed
		if (SimpleGUI::Button("Button", Vec2(640, 40)))
		{
			// Move the coordinates to a random position in the screen
			emojiPos = RandomVec2(Scene::Rect());
		}
	}
}
