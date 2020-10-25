
# include <Siv3D.hpp> // OpenSiv3D v0.6
SIV3D_SET(EngineOption::Renderer::Direct3D11)
//SIV3D_SET(EngineOption::Renderer::OpenGL)
//SIV3D_SET(EngineOption::D3D11Driver::Hardware)

void Siv3DTest();

void Main()
{
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::Resize(800, 800);
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	//const VertexShader vs = HLSL(U"vs.hlsl")
	//	| GLSL(U"vs.vert", { {U"VSConstants2D", 0} }) | MSL(U"VS");

	//const PixelShader ps = HLSL(U"ps.hlsl")
	//	| GLSL(U"ps.frag", { {U"PSConstants2D", 0} }) | MSL(U"PS");

	while (System::Update())
	{
		for (auto i : step(20))
		{
			Rect(Cursor::Pos().movedBy(0 + i * 20, 0), 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}
	}
}
