<h1>OpenSiv3D <a href="https://github.com/Siv3D/OpenSiv3D/blob/master/LICENSE"><img src="https://img.shields.io/badge/license-MIT-4aaa4a"></a> <a href="https://join.slack.com/t/siv3d/shared_invite/enQtNjM4NzQ0MzEyMzUzLTEzNDBkNWVkMTY0OGU5OWQxOTk3NjczMjk0OGJhYzJjOThjZjQ1YmYzMWU2NzQ5NTQ4ODg3NzE2ZmE0NmVlMTM"><img src="https://img.shields.io/badge/social-Slack-4a154b"></a> <a href="https://twitter.com/search?q=Siv3D%20OR%20OpenSiv3D&src=typed_query&f=live"><img src="https://img.shields.io/badge/social-Twitter-1DA1F2"></a> <a href="https://github.com/sponsors/Reputeless"><img src="https://img.shields.io/badge/funding-GitHub_Sponsors-ea4aaa"></a></h1>

**OpenSiv3D** is a C++20 framework for creative coding.

## Installation Guide & Documentation

- English: https://siv3d.github.io/
- 日本語: https://siv3d.github.io/ja-jp/

## SDK Downloads

| Platform           | Version    | Date       | Requirements                  |
|:------------------:|:----------:|:----------:|:------------------------------|
| Windows            | **0.6.0**  | ?? ?? 2021 | - Windows 7 SP1 / 8.1 / Windows 10 (64-bit)<br>- Microsoft Visual C++ 2019 16.10<br>- Windows 10 SDK<br>- Intel / AMD CPU |
| macOS              | **0.6.0**  | ?? ?? 2021 | - macOS Mojave / Catalina / Big Sur<br>- Xcode 11.3 or newer (Big Sur requires Xcode 12.5)<br>- Intel CPU<br>- OpenGL 4.1 compatible graphics card |
| Linux              | **0.6.0*** | ?? ?? 2021 | - GCC 9.3.0<br>- Intel / AMD CPU<br>- OpenGL 4.1 compatible graphics card |
| Web (experimental) | **0.6.0*** | ?? ?? 2021 | - Emscripten 2.0.22 or newer<br>- Brower with WebAssembly and WebGL2 support |

<small>* Some functionality may be missing or limited</small>

## Quick Links
- [Documentation](https://zenn.dev/reputeless/books/siv3d-documentation)
- [Roadmap](https://zenn.dev/reputeless/articles/opensiv3d-roadmap)
- [Open Source Software used in OpenSiv3D](ThirdParty.md)
- [Architecture](ARCHITECTURE.md)

## Examples

### 1. Hello, Siv3D!

```cpp
# include <Siv3D.hpp>

void Main()
{
	// Set background color to sky blue
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// Create a new font
	const Font font{ 60 };
	
	// Create a new emoji font
	const Font emojiFont{ 60, Typeface::ColorEmoji };
	
	// Set emojiFont as a fallback
	font.addFallback(emojiFont);

	// Create a texture from an image file
	const Texture texture{ U"example/windmill.png" };

	// Create a texture from an emoji
	const Texture emoji{ U"🐈"_emoji };

	// Coordinates of the emoji
	Vec2 emojiPos{ 300, 150 };

	// Print a text
	Print << U"Push [A] key";

	while (System::Update())
	{
		// Draw a texture
		texture.draw(200, 200);

		// Put a text in the middle of the screen
		font(U"Hello, Siv3D!🚀").drawAt(Scene::Center(), Palette::Black);

		// Draw a texture with animated size
		emoji.resized(100 + Periodic::Sine0_1(1s) * 20).drawAt(emojiPos);

		// Draw a red transparent circle that follows the mouse cursor
		Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1, 0, 0, 0.5 });

		// When [A] key is down
		if (KeyA.down())
		{
			// Print a randomly selected text
			Print << Sample({ U"Hello!", U"こんにちは", U"你好", U"안녕하세요?" });
		}

		// When [Button] is pushed
		if (SimpleGUI::Button(U"Button", Vec2{ 640, 40 }))
		{
			// Move the coordinates to a random position in the screen
			emojiPos = RandomVec2(Scene::Rect());
		}
	}
}
```
