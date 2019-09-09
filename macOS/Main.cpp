# include <Siv3D.hpp> // OpenSiv3D v0.4.1

namespace s3d
{
	namespace Shader
	{
		void DownSample(const TextureRegion& textureRegion, RenderTexture& rt)
		{
			ScopedRenderTarget2D target(rt);
			ScopedRenderStates2D states(BlendState::Default, SamplerState::ClampLinear, RasterizerState::Default2D);
			textureRegion.resized(rt.size()).draw();
		}
		
		void GaussianBlurH(const PixelShader& ps, const TextureRegion& textureRegion, RenderTexture& rt)
		{
			const Float4 value(Float2(1.0f, 1.0f) / textureRegion.texture.size(), Float2(1.0f, 0.0f));
			Graphics2D::Internal::SetInternalConstantBufferValue(ShaderStage::Pixel, value);
			{
				ScopedCustomShader2D shader(ps);
				ScopedRenderTarget2D target(rt);
				textureRegion.draw();
			}
		}
		
		void GaussianBlurV(const PixelShader& ps, const TextureRegion& textureRegion, RenderTexture& rt)
		{
			const Float4 value(Float2(1.0f, 1.0f) / textureRegion.texture.size(), Float2(0.0f, 1.0f));
			Graphics2D::Internal::SetInternalConstantBufferValue(ShaderStage::Pixel, value);
			{
				ScopedCustomShader2D shader(ps);
				ScopedRenderTarget2D target(rt);
				textureRegion.draw();
			}
		}
	}
}

void Main()
{
	Window::Resize(1280, 720);
	//const PixelShader gaussianBlur(U"example/shader/gaussian_blur_5.hlsl");
	//const PixelShader gaussianBlur(U"example/shader/gaussian_blur_9.hlsl");
	const PixelShader gaussianBlur(U"example/shader/gaussian_blur_13.frag",
								   {{ U"PSConstants2D", 0 }});
	const Texture texture(Image(U"example/bay.jpg").scale(1280, 720));
	//const Texture texture(U"example/siv3d-kun.png");
	const Size size = texture.size();
	
	RenderTexture rtA(size, ColorF(0.0)), rtB(size, ColorF(0.0));
	RenderTexture rtA2(size/2, ColorF(0.0)), rtB2(size/2, ColorF(0.0));
	RenderTexture rtA4(size / 4, ColorF(0.0)), rtB4(size / 4, ColorF(0.0));
	RenderTexture rtA8(size / 8, ColorF(0.0)), rtB8(size / 8, ColorF(0.0));
	size_t index = 0;
	
	while (System::Update())
	{
		if (MouseL.down())
		{
			++index %= 4;
		}
		
		if (index == 0)
		{
			texture.draw();
			continue;
		}
		
		Shader::GaussianBlurH(gaussianBlur, texture, rtA);
		Shader::GaussianBlurV(gaussianBlur, rtA, rtB);
		
		Shader::DownSample(rtB, rtB2);
		
		Shader::GaussianBlurH(gaussianBlur, rtB2, rtA2);
		Shader::GaussianBlurV(gaussianBlur, rtA2, rtB2);
		
		Shader::DownSample(rtB2, rtB4);
		
		Shader::GaussianBlurH(gaussianBlur, rtB4, rtA4);
		Shader::GaussianBlurV(gaussianBlur, rtA4, rtB4);
		
		Shader::DownSample(rtB4, rtB8);
		
		Shader::GaussianBlurH(gaussianBlur, rtB8, rtA8);
		Shader::GaussianBlurV(gaussianBlur, rtA8, rtB8);

		texture.draw();

		const Vec2 pos = Cursor::PosF();
		const RoundRect rr(pos, 600, 400, 8);
		rr(rtB8(pos / 8, 75, 50).scaled(8)).draw();
		
		if (2 <= index)
		{
			rr.draw(ColorF(1.0, 0.7));
		}
		
		if (3 <= index)
		{
			RoundRect(rr.rect.pos, rr.rect.w, 40, rr.r).draw(ColorF(0.5));
			RectF(rr.rect.pos, rr.rect.w, 40).stretched(-rr.r, 0,0,0).draw(ColorF(0.5));
		}
		
		if (3 <= index)
		{
			rr.drawFrame(2, 0, ColorF(0.5));
		}
	}
}
