# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	const Texture texture(Emoji(L"👨‍🚀"), TextureDesc::Mipped);
	Graphics::SetBackground(Palette::Skyblue);
	
	while (System::Update())
	{
		RenderStateBlock2D rb(SamplerState::ClampNearest);
		
		texture.scale(3.3).drawAt(Window::Center());
	}
}
