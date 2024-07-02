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
  - Unicode 15.1 emojis and 7,000+ icons
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
  - OSC (Open Sound Control)
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
  - JSON Validation
- **Misc**
  - Basic GUI (button, slider, radio buttons, checkbox, text box, color picker, list box, menu bar, table)
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
  - OpenAI API (Chat, Vision, Image, Speech, Embedding)

<small>* Some features are limited to specific platforms</small>

## How to Install Siv3D + Tutorial

- **(English) Getting Started with Siv3D:** https://siv3d.github.io/en-us/
- **(日本語) Siv3D をはじめよう:** https://siv3d.github.io/ja-jp/

**v0.6.15** | *released 3 July 2024* | [Release Notes](https://siv3d.github.io/ja-jp/releases/)

| Platform           | SDK  | Requirements                  |
|:------------------:|:----------:|:------------------------------|
| Windows            | [**Download SDK**](https://siv3d.github.io/en-us/download/windows/) /<br>[**SDK をダウンロード**](https://siv3d.github.io/ja-jp/download/windows/) | - Windows 10 / 11 (64-bit)<br>- Microsoft Visual C++ 2022 17.9<br>- Windows 10 SDK<br>- Intel / AMD CPU |
| macOS              | [**Download SDK**](https://siv3d.github.io/en-us/download/macos/) /<br>[**SDK をダウンロード**](https://siv3d.github.io/ja-jp/download/macos/) | - macOS Big Sur / Monterey / Ventura<br>- Xcode 12.5 or newer<br>- Intel CPU / Apple Silicon (Rosetta mode)*<br>- OpenGL 4.1 compatible hardware |
| Linux              | [**Compiling for Linux**](https://siv3d.github.io/en-us/download/ubuntu/) /<br>[**Linux 版のビルド**](https://siv3d.github.io/ja-jp/download/ubuntu/) | - GCC 9.3.0 (with Boost 1.71.0) / GCC 11.2 (with Boost 1.74.0)<br>- Intel / AMD CPU<br>- OpenGL 4.1 compatible hardware |
| Web (experimental**) | [**Compiling for Web**](https://siv3d.kamenokosoft.com/docs/en/) /<br>[**Web 版のビルド**](https://siv3d.kamenokosoft.com/docs/ja/) | Web browser with WebAssembly and WebGL2 support |

<small>* Native Apple Silicon support will be added in the future release. You can build and run Siv3D in Rosetta mode</small><br><small>** Some functionality may be missing or limited</small>

## Next Major Update

The next major update, Siv3D v0.8, is under development in the following repository.
- https://github.com/Siv3D/siv8

## Community

- [Siv3D Discord Server](https://discord.gg/mzevvsY)


## Miscellaneous

- [Open Source Software used in Siv3D](ThirdParty.md)
- [Architecture](ARCHITECTURE.md)


## Supporting the Project

If you would like to support the project financially, visit my GitHub Sponsors page. Your support will accelerate the development of this exciting framework.

💗 https://github.com/sponsors/Reputeless


## Examples

### 1. Hello, Siv3D!

![Screenshot](https://raw.githubusercontent.com/Siv3D/File/master/v6/screenshot/hello.gif)

```cpp
# include <Siv3D.hpp>

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	// 画像ファイルからテクスチャを作成する | Create a texture from an image file
	const Texture texture{ U"example/windmill.png" };

	// 絵文字からテクスチャを作成する | Create a texture from an emoji
	const Texture emoji{ U"🦖"_emoji };

	// 太文字のフォントを作成する | Create a bold font with MSDF method
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	// テキストに含まれる絵文字のためのフォントを作成し、font に追加する | Create a font for emojis in text and add it to font as a fallback
	const Font emojiFont{ 48, Typeface::ColorEmoji };
	font.addFallback(emojiFont);

	// ボタンを押した回数 | Number of button presses
	int32 count = 0;

	// チェックボックスの状態 | Checkbox state
	bool checked = false;

	// プレイヤーの移動スピード | Player's movement speed
	double speed = 200.0;

	// プレイヤーの X 座標 | Player's X position
	double playerPosX = 400;

	// プレイヤーが右を向いているか | Whether player is facing right
	bool isPlayerFacingRight = true;

	while (System::Update())
	{
		// テクスチャを描く | Draw the texture
		texture.draw(20, 20);

		// テキストを描く | Draw text
		font(U"Hello, Siv3D!🎮").draw(64, Vec2{ 20, 340 }, ColorF{ 0.2, 0.4, 0.8 });

		// 指定した範囲内にテキストを描く | Draw text within a specified area
		font(U"Siv3D (シブスリーディー) は、ゲームやアプリを楽しく簡単な C++ コードで開発できるフレームワークです。")
			.draw(18, Rect{ 20, 430, 480, 200 }, Palette::Black);

		// 長方形を描く | Draw a rectangle
		Rect{ 540, 20, 80, 80 }.draw();

		// 角丸長方形を描く | Draw a rounded rectangle
		RoundRect{ 680, 20, 80, 200, 20 }.draw(ColorF{ 0.0, 0.4, 0.6 });

		// 円を描く | Draw a circle
		Circle{ 580, 180, 40 }.draw(Palette::Seagreen);

		// 矢印を描く | Draw an arrow
		Line{ 540, 330, 760, 260 }.drawArrow(8, SizeF{ 20, 20 }, ColorF{ 0.4 });

		// 半透明の円を描く | Draw a semi-transparent circle
		Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1.0, 0.0, 0.0, 0.5 });

		// ボタン | Button
		if (SimpleGUI::Button(U"count: {}"_fmt(count), Vec2{ 520, 370 }, 120, (checked == false)))
		{
			// カウントを増やす | Increase the count
			++count;
		}

		// チェックボックス | Checkbox
		SimpleGUI::CheckBox(checked, U"Lock \U000F033E", Vec2{ 660, 370 }, 120);

		// スライダー | Slider
		SimpleGUI::Slider(U"speed: {:.1f}"_fmt(speed), speed, 100, 400, Vec2{ 520, 420 }, 140, 120);

		// 左キーが押されていたら | If left key is pressed
		if (KeyLeft.pressed())
		{
			// プレイヤーが左に移動する | Player moves left
			playerPosX = Max((playerPosX - speed * Scene::DeltaTime()), 60.0);
			isPlayerFacingRight = false;
		}

		// 右キーが押されていたら | If right key is pressed
		if (KeyRight.pressed())
		{
			// プレイヤーが右に移動する | Player moves right
			playerPosX = Min((playerPosX + speed * Scene::DeltaTime()), 740.0);
			isPlayerFacingRight = true;
		}

		// プレイヤーを描く | Draw the player
		emoji.scaled(0.75).mirrored(isPlayerFacingRight).drawAt(playerPosX, 540);
	}
}
```

### 2. Breakout

![Screenshot](https://raw.githubusercontent.com/Siv3D/File/master/v6/screenshot/breakout-v067.gif)

```cpp
# include <Siv3D.hpp>

void Main()
{
	// 1 つのブロックのサイズ | Size of a single block
	constexpr Size BrickSize{ 40, 20 };

	// ボールの速さ（ピクセル / 秒） | Ball speed (pixels / second)
	constexpr double BallSpeedPerSec = 480.0;

	// ボールの速度 | Ball velocity
	Vec2 ballVelocity{ 0, -BallSpeedPerSec };

	// ボール | Ball
	Circle ball{ 400, 400, 8 };

	// ブロックの配列 | Array of bricks
	Array<Rect> bricks;

	for (int32 y = 0; y < 5; ++y)
	{
		for (int32 x = 0; x < (Scene::Width() / BrickSize.x); ++x)
		{
			bricks << Rect{ (x * BrickSize.x), (60 + y * BrickSize.y), BrickSize };
		}
	}

	while (System::Update())
	{
		// パドル | Paddle
		const Rect paddle{ Arg::center(Cursor::Pos().x, 500), 60, 10 };

		// ボールを移動させる | Move the ball
		ball.moveBy(ballVelocity * Scene::DeltaTime());

		// ブロックを順にチェックする | Check bricks in sequence
		for (auto it = bricks.begin(); it != bricks.end(); ++it)
		{
			// ブロックとボールが交差していたら | If block and ball intersect
			if (it->intersects(ball))
			{
				// ブロックの上辺、または底辺と交差していたら | If ball intersects with top or bottom of the block
				if (it->bottom().intersects(ball) || it->top().intersects(ball))
				{
					// ボールの速度の Y 成分の符号を反転する | Reverse the sign of the Y component of the ball's velocity
					ballVelocity.y *= -1;
				}
				else // ブロックの左辺または右辺と交差していたら
				{
					// ボールの速度の X 成分の符号を反転する | Reverse the sign of the X component of the ball's velocity
					ballVelocity.x *= -1;
				}

				// ブロックを配列から削除する（イテレータは無効になる） | Remove the block from the array (the iterator becomes invalid)
				bricks.erase(it);

				// これ以上チェックしない | Do not check any more
				break;
			}
		}

		// 天井にぶつかったら | If the ball hits the ceiling
		if ((ball.y < 0) && (ballVelocity.y < 0))
		{
			// ボールの速度の Y 成分の符号を反転する | Reverse the sign of the Y component of the ball's velocity
			ballVelocity.y *= -1;
		}

		// 左右の壁にぶつかったら | If the ball hits the left or right wall
		if (((ball.x < 0) && (ballVelocity.x < 0))
			|| ((Scene::Width() < ball.x) && (0 < ballVelocity.x)))
		{
			// ボールの速度の X 成分の符号を反転する | Reverse the sign of the X component of the ball's velocity
			ballVelocity.x *= -1;
		}

		// パドルにあたったら | If the ball hits the left or right wall
		if ((0 < ballVelocity.y) && paddle.intersects(ball))
		{
			// パドルの中心からの距離に応じてはね返る方向（速度ベクトル）を変える | Change the direction (velocity vector) of the ball depending on the distance from the center of the paddle
			ballVelocity = Vec2{ (ball.x - paddle.center().x) * 10, -ballVelocity.y }.setLength(BallSpeedPerSec);
		}

		// すべてのブロックを描画する | Draw all the bricks
		for (const auto& brick : bricks)
		{
			// ブロックの Y 座標に応じて色を変える | Change the color of the brick depending on the Y coordinate
			brick.stretched(-1).draw(HSV{ brick.y - 40 });
		}

		// マウスカーソルを非表示にする | Hide the mouse cursor
		Cursor::RequestStyle(CursorStyle::Hidden);

		// ボールを描く | Draw the ball
		ball.draw();

		// パドルを描く | Draw the paddle
		paddle.rounded(3).draw();
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
