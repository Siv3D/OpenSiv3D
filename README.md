<h1>Siv3D <a href="https://github.com/Siv3D/OpenSiv3D/blob/master/LICENSE"><img src="https://img.shields.io/badge/license-MIT-4aaa4a"></a> <a href="https://join.slack.com/t/siv3d/shared_invite/enQtNjM4NzQ0MzEyMzUzLTEzNDBkNWVkMTY0OGU5OWQxOTk3NjczMjk0OGJhYzJjOThjZjQ1YmYzMWU2NzQ5NTQ4ODg3NzE2ZmE0NmVlMTM"><img src="https://img.shields.io/badge/social-Slack-4a154b"></a> <a href="https://twitter.com/search?q=Siv3D%20OR%20OpenSiv3D&src=typed_query&f=live"><img src="https://img.shields.io/badge/social-Twitter-1DA1F2"></a> <a href="https://github.com/sponsors/Reputeless"><img src="https://img.shields.io/badge/funding-GitHub_Sponsors-ea4aaa"></a></h1>

<p align="center"><a href="https://siv3d.github.io/"><img src="https://raw.githubusercontent.com/Siv3D/File/master/v6/logo.png" width="480" alt="Siv3D logo"></a></p>

**Siv3D** (OpenSiv3D) is a C++20 framework for creative coding.

# v0.6.0 beta 5 (pre-release)

## SDK Downloads

| Platform           | Version    | Date       | Requirements                  |
|:------------------:|:----------:|:----------:|:------------------------------|
| Windows            | [**0.6.0 beta 5**](https://siv3d.jp/downloads/Siv3D/OpenSiv3D_0.6.0_b5Installer.exe)  | 2 September 2021 | - Windows 7 SP1 / 8.1 / Windows 10 (64-bit)<br>- Microsoft Visual C++ 2019 16.10<br>- Windows 10 SDK<br>- Intel / AMD CPU |
| macOS              | [**0.6.0 beta 5**](https://siv3d.jp/downloads/Siv3D/siv3d_v0.6.0_b4_macOS.zip)  | 2 September 2021 | - macOS Mojave / Catalina / Big Sur<br>- Xcode 11.3 or newer (Big Sur requires Xcode 12.5)<br>- Intel CPU<br>- OpenGL 4.1 compatible graphics card |
| Linux              | [**0.6.0 beta 5***](https://zenn.dev/reputeless/books/siv3d-documentation/viewer/setup) | 2 September 2021 | - GCC 9.3.0<br>- Intel / AMD CPU<br>- OpenGL 4.1 compatible graphics card |
| Web (experimental) | [**0.6.0b0**](https://github.com/nokotan/OpenSiv3D/releases)* | August 2021 | - Emscripten 2.0.22 or newer<br>- Browser with WebAssembly and WebGL2 support |

<small>* Some functionality may be missing or limited</small>

## Installation Guide & Documentation (v0.6.0)

- [Documentation (日本語)](https://zenn.dev/reputeless/books/siv3d-documentation)
- Documentation (English)
- [Roadmap](https://zenn.dev/reputeless/articles/opensiv3d-roadmap)
- [Open Source Software used in Siv3D](ThirdParty.md)
- [Architecture](ARCHITECTURE.md)


# v0.4.3 (stable)

## Installation Guide & Documentation (v0.4.3)

- English: https://siv3d.github.io/
- 日本語: https://siv3d.github.io/ja-jp/

## SDK Downloads

| Platform        | Version        | Date       | Requirements                  |
|:---------------:|:---------------:|:-------------:|:------------------------------|
| Windows | [**0.4.3**](https://siv3d.github.io/#getting-started) | 11 April 2020 | - Windows 7 SP1 / 8.1 / 10 (64-bit)<br>- Microsoft Visual C++ 2019 16.4<br>- Windows 10 SDK |
| macOS           | [**0.4.3**](https://siv3d.github.io/#getting-started) | 11 April 2020 | - macOS Mojave v10.14 or newer<br>- Xcode 11.3 or newer<br>- OpenGL 4.1 compatible graphics card |
| Linux           | [**0.4.3**](https://siv3d.github.io/#getting-started)* | 11 April 2020 | - Tested compilers: Clang 8.0.1 / GCC 9.1.0<br>- OpenGL 4.1 compatible graphics card |

# Examples (v0.6.0)

### 1. Hello, Siv3D!

![Screenshot](https://raw.githubusercontent.com/Siv3D/File/master/v6/screenshot/hello-siv3d.gif)

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

### 2. Breakout

![Screenshot](https://raw.githubusercontent.com/Siv3D/File/master/v6/screenshot/breakout.gif)

```cpp
# include <Siv3D.hpp>

void Main()
{
	constexpr Size brickSize{ 40, 20 };
	
	constexpr double speed = 480.0;
	
	Vec2 ballVelocity{ 0, -speed };
	
	Circle ball{ 400, 400, 8 };

	Array<Rect> bricks;
	for (auto p : step(Size{ (Scene::Width() / brickSize.x), 5 }))
	{
		bricks << Rect{ (p.x * brickSize.x), (60 + p.y * brickSize.y), brickSize };
	}

	while (System::Update())
	{
		const Rect paddle{ Arg::center(Cursor::Pos().x, 500), 60, 10 };

		ball.moveBy(ballVelocity * Scene::DeltaTime());

		for (auto it = bricks.begin(); it != bricks.end(); ++it)
		{
			if (it->intersects(ball))
			{
				(it->bottom().intersects(ball) || it->top().intersects(ball)
					? ballVelocity.y : ballVelocity.x) *= -1;

				bricks.erase(it);
				break;
			}
		}

		if (ball.y < 0 && ballVelocity.y < 0)
		{
			ballVelocity.y *= -1;
		}

		if ((ball.x < 0 && ballVelocity.x < 0)
			|| (Scene::Width() < ball.x && 0 < ballVelocity.x))
		{
			ballVelocity.x *= -1;
		}

		if (0 < ballVelocity.y && paddle.intersects(ball))
		{
			ballVelocity = Vec2{ (ball.x - paddle.center().x) * 10, -ballVelocity.y }.setLength(speed);
		}

		for (const auto& brick : bricks)
		{
			brick.stretched(-1).draw(HSV{ brick.y - 40 });
		}

		ball.draw();
		paddle.draw();
	}
}
```

### 3. Hello, 3D world! 

![Screenshot](https://raw.githubusercontent.com/Siv3D/File/master/v6/screenshot/hello-3d.png)

```cpp
# include <Siv3D.hpp>

void Main()
{
	// Resize the window and scene to 1280x720
	Window::Resize(1280, 720);

	// Background color (remove SRGB curve for a linear workflow)
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();

	// Texture for UV check (mipmapped. treat as SRGB texture in a linear workflow)
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };

	// Multisample RenderTexture for a linear workflow
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

	// 3D debug camera (free camera)
	// Vertical FOV: 30°, Eye position: (10, 16, -32)
	// Move: [W][S][A][D][E][X], View: [arrow keys]
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };

	while (System::Update())
	{
		// Update a camera
		camera.update(2.0);

		// Set up a camera in the current 3D scene
		Graphics3D::SetCameraTransform(camera);

		// [3D rendering]
		{
			// Clear renderTexture with the background color,
			// then make renderTexture the render target for the current 3D scene
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

			// Draw a floor
			Plane{ 64 }.draw(uvChecker);

			// Draw a box
			Box{ -8,2,0,4 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());

			// Draw a sphere
			Sphere{ 0,2,0,2 }.draw(ColorF{ 0.4, 0.8, 0.6 }.removeSRGBCurve());

			// Draw a cylinder
			Cylinder{ 8, 2, 0, 2, 4 }.draw(ColorF{ 0.6, 0.4, 0.8 }.removeSRGBCurve());
		}

		// [2D rendering]
		{
			// Flush 3D rendering commands before multisample resolve
			Graphics3D::Flush();

			// Multisample resolve
			renderTexture.resolve();

			// Transfer renderTexture to the current 2D scene (default scene)
			Shader::LinearToScreen(renderTexture);
		}
	}
}
```