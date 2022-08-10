<h1>Siv3D <a href="https://github.com/Siv3D/OpenSiv3D/blob/master/LICENSE"><img src="https://img.shields.io/badge/license-MIT-4aaa4a"></a> <a href="https://discord.gg/mzevvsY"><img src="https://img.shields.io/badge/social-Discord-404eed"></a> <a href="https://twitter.com/search?q=Siv3D%20OR%20OpenSiv3D&src=typed_query&f=live"><img src="https://img.shields.io/badge/social-Twitter-1DA1F2"></a> <a href="https://github.com/sponsors/Reputeless"><img src="https://img.shields.io/badge/funding-GitHub_Sponsors-ea4aaa"></a></h1>

<p align="center"><a href="https://siv3d.github.io/"><img src="https://raw.githubusercontent.com/Siv3D/File/master/v6/logo.png" width="480" alt="Siv3D logo"></a></p>

**Siv3D** (OpenSiv3D) is a C++20 framework for **creative coding** (2D/3D games, media art, visualizers, and simulators). Siv3D applications run on **Windows, macOS, Linux, and the Web**.


## Features

- **Graphics**
  - Advanced 2D graphics
  - Basic 3D graphics (Wavefront OBJ, primitive shapes)
  - Custom vertex / pixel shaders (HLSL, GLSL)
  - Text rendering (Bitmap, SDF, MSDF)
  - PNG, JPEG, BMP, SVG, GIF, Animated GIF, TGA, PPM, WebP, TIFF
  - Unicode 14.0 emojis and 7,000+ icons
  - Image processing
  - Video rendering
- **Audio** 
  - WAVE, MP3, AAC, OggVorbis, Opus, MIDI, WMA*, FLAC*, AIFF*
  - Adjustable volume, pan, play speed and pitch
  - File streaming (WAVE, MP3, OggVorbis)
  - Fade in and fade out
  - Looping
  - Mixing busses
  - Filters (LPF, HPF, echo, reverb)
  - FFT
  - SoundFont rendering
  - Text to speech*
- **Input**
  - Mouse
  - Keyboard
  - Gamepad
  - Webcam
  - Microphone
  - Joy-Con / Pro Controller
  - XInput*
  - Digital drawing tablet*
  - Leap Motion*
- **Window**
  - Fullscreen mode
  - High DPI support
  - Window styles (sizable, borderless)
  - File dialog
  - Drag & drop
  - Message box
  - Toast notification*
- **Network and communication**
  - HTTP client
  - Multiplayer (with Photon SDK)
  - TCP communication
  - Serial communication
  - Interprocess communication (pipe)
- **Math**
  - Vector and matrix classes (`Point`, `Float2`, `Vec2`, `Float3`, `Vec3`, `Float4`, `Vec4`, `Mat3x2`, `Mat3x3`, `Mat4x4`, `SIMD_Float4`, `Quaternion`)
  - 2D shape classes (`Line`, `Circle`, `Ellipse`, `Rect`, `RectF`, `Triangle`, `Quad`, `RoundRect`, `Polygon`, `MultiPolygon`, `LineString`, `Spline2D`, `Bezier2`, `Bezier3`)
  - 3D shape classes (`Plane`, `InfinitePlane`, `Sphere`, `Box`, `OrientedBox`, `Ray`, `Line3D`, `Triangle3D`, `ViewFrustum`, `Disc`, `Cylinder`, `Cone`)
  - Color classes (`Color`, `ColorF`, `HSV`)
  - Polar / cylindrical / spherical coordinates system
  - 2D / 3D shape intersection
  - 2D / 3D geometry processing
  - Rectangle packing
  - Planar subdivisions
  - Linear and gamma color space
  - Pseudo random number generators
  - Interpolation, easing, and smoothing
  - Perlin noise
  - Math parser
  - Navigation mesh
  - Extended arithmetic types (`HalfFloat`, `int128`, `uint128`, `BigInt`, `BigFloat`)
- **String and Text Processing**
  - Advanced String class (`String`, `StringView`)
  - Unicode conversion
  - Regular expression
  - `{fmt}` style text formatting
  - Text reader / writer classes
  - CSV / INI / JSON / XML / TOML reader classes
  - CSV / INI / JSON writer classes
- **Misc**
  - Basic GUI (button, slider, radio buttons, checkbox, text box, color picker, list box)
  - Integrated 2D physics engine (Box2D)
  - Advanced array / 2D array classes (`Array`, `Grid`)
  - Kd-tree
  - Disjoint set
  - Asynchronous asset file streaming
  - Data compression (zlib, Zstandard)
  - Transitions between scenes
  - File system
  - Directory watcher
  - QR code reader / writer
  - GeoJSON
  - Date and time
  - Stopwatch and timer
  - Logging
  - Serialization
  - UUID
  - Child process
  - Clipboard
  - Power status
  - Scripting (AngelScript)

<small>* Some features are limited to specific platforms</small>

## How to Install Siv3D + Tutorial

- **(English) Getting Started with Siv3D:** https://siv3d.github.io/
- **(日本語) Siv3D をはじめよう:** https://siv3d.github.io/ja-jp/

**v0.6.5** | *released 10 August 2022* | [Release Notes](https://siv3d.github.io/ja-jp/releases/)

| Platform           | SDK  | Requirements                  |
|:------------------:|:----------:|:------------------------------|
| Windows            | [**Download SDK**](https://siv3d.github.io/download/windows/) /<br>[**SDK をダウンロード**](https://siv3d.github.io/ja-jp/download/windows/) | - Windows 7 SP1 / 8.1 / 10 / 11 (64-bit)<br>- Microsoft Visual C++ 2022 17.3<br>- Windows 10 SDK<br>- Intel / AMD CPU |
| macOS              | [**Download SDK**](https://siv3d.github.io/download/macos/) /<br>[**SDK をダウンロード**](https://siv3d.github.io/ja-jp/download/macos/) | - macOS Mojave / Catalina / Big Sur / Monterey<br>- Xcode 11.3 or newer (Big Sur requires Xcode 12.5 or newer)<br>- Intel CPU / Apple Silicon (Rosetta mode)*<br>- OpenGL 4.1 compatible hardware |
| Linux              | [**Compiling for Linux**](https://siv3d.github.io/download/ubuntu/) /<br>[**Linux 版のビルド**](https://siv3d.github.io/ja-jp/download/ubuntu/) | - GCC 9.3.0 (with Boost 1.71.0) / GCC 11.2 (with Boost 1.74.0)<br>- Intel / AMD CPU<br>- OpenGL 4.1 compatible hardware |
| Web (experimental**) | [**Compiling for Web**](https://siv3d.kamenokosoft.com/download) /<br>[**Web 版のビルド**](https://siv3d.kamenokosoft.com/ja/download) | Web browser with WebAssembly and WebGL2 support |

<small>* Native Apple Silicon support will be added in the future release. You can build and run Siv3D in Rosetta mode</small><br><small>** Some functionality may be missing or limited</small>


## Community

- [Siv3D Discord Server](https://discord.gg/mzevvsY)


## Miscellaneous

- [Open Source Software used in Siv3D](ThirdParty.md)
- [Architecture](ARCHITECTURE.md)
- [Roadmap](https://zenn.dev/reputeless/articles/opensiv3d-roadmap)


## Supporting the Project

If you would like to support the project financially, visit my GitHub Sponsors page. Your support will accelerate the development of this exciting framework.

💗 https://github.com/sponsors/Reputeless


## Examples

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

> [Web Demo](https://siv3d.jp/web/sample/breakout/breakout.html)

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

> [Web Demo](https://siv3d.jp/web/sample/basic3d/basic3d.html)

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
