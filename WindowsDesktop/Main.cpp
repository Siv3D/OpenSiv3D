# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	Window::Resize(1280, 720);
	const Texture texture(Image(U"example/bay.jpg").scale(1280, 720));

	constexpr Size blurAreaSize(480, 320);
	RenderTexture rtA(blurAreaSize), rtB(blurAreaSize);
	RenderTexture rtA4(blurAreaSize / 4), rtB4(blurAreaSize / 4);
	RenderTexture rtA8(blurAreaSize / 8), rtB8(blurAreaSize / 8);

	while (System::Update())
	{
		const Point cursorPos = Cursor::Pos();
		const Rect blurArea(cursorPos, blurAreaSize);

		Shader::GaussianBlur(texture(blurArea), rtB, rtA);
		Shader::Downsample(rtA, rtA4);
		Shader::GaussianBlur(rtA4, rtB4, rtA4);
		Shader::Downsample(rtA4, rtA8);
		Shader::GaussianBlur(rtA8, rtB8, rtA8);

		texture.draw();
		RoundRect(cursorPos, blurAreaSize, 40)(rtA8.resized(blurAreaSize)).draw();
	}
}