//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3DEngine.hpp>
# include <Shader/IShader.hpp>
# include <Siv3D/Shader.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/ScopedCustomShader2D.hpp>
# include <Siv3D/ScopedRenderTarget2D.hpp>
# include <Siv3D/ScopedRenderStates2D.hpp>

namespace s3d
{
	namespace Shader
	{
		void Copy(const TextureRegion& from, RenderTexture& to)
		{
			if (!from.texture)
			{
				throw Error(U"Shader::Copy(): !from.texture");
			}

			if (!to)
			{
				throw Error(U"Shader::Copy(): !to");
			}

			if (from.size != to.size())
			{
				throw Error(U"Shader::Copy(): from.size != to.size()");
			}

			if (from.texture == to)
			{
				throw Error(U"Shader::Copy(): from.texture == to");
			}

			ScopedRenderTarget2D target(to);
			ScopedRenderStates2D states(BlendState::Opaque, SamplerState::ClampNearest, RasterizerState::Default2D);
			ScopedCustomShader2D shader(Siv3DEngine::Get<ISiv3DShader>()->getEnginePS(EnginePS::Copy));
			from.draw();
		}

		void Downsample(const TextureRegion& from, RenderTexture& to)
		{
			if (!from.texture)
			{
				throw Error(U"Shader::DownSample(): !from.texture");
			}

			if (!to)
			{
				throw Error(U"Shader::DownSample(): !to");
			}

			if (from.texture == to)
			{
				throw Error(U"Shader::DownSample(): from.texture == to");
			}

			ScopedRenderTarget2D target(to);
			ScopedRenderStates2D states(BlendState::Opaque, SamplerState::ClampLinear, RasterizerState::Default2D);
			ScopedCustomShader2D shader(Siv3DEngine::Get<ISiv3DShader>()->getEnginePS(EnginePS::Copy));
			from.resized(to.size()).draw();
		}

		void GaussianBlurH(const TextureRegion& from, RenderTexture& to)
		{
			GaussianBlur(from, to, Vec2(1, 0));
		}

		void GaussianBlurV(const TextureRegion& from, RenderTexture& to)
		{
			GaussianBlur(from, to, Vec2(0, 1));
		}

		void GaussianBlur(const TextureRegion& from, RenderTexture& to, const Vec2& direction)
		{
			if (!from.texture)
			{
				throw Error(U"Shader::GaussianBlur(): !from.texture");
			}

			if (!to)
			{
				throw Error(U"Shader::GaussianBlur(): !to");
			}

			if (from.size != to.size())
			{
				throw Error(U"Shader::GaussianBlur(): from.size != to.size()");
			}

			if (from.texture == to)
			{
				throw Error(U"Shader::GaussianBlur(): from.texture == to");
			}
			
			ScopedRenderTarget2D target(to);
			ScopedRenderStates2D states(BlendState::Opaque, SamplerState::ClampLinear, RasterizerState::Default2D);
			ScopedCustomShader2D shader(Siv3DEngine::Get<ISiv3DShader>()->getEnginePS(EnginePS::GaussianBlur_9));
			Graphics2D::Internal::SetInternalConstantBufferValue(ShaderStage::Pixel, Float4(Float2(1, 1) / from.size * Float2(from.uvRect.right - from.uvRect.left, from.uvRect.bottom - from.uvRect.top), direction));
			from.draw();
		}

		void GaussianBlur(const TextureRegion& from, RenderTexture& internalBuffer, RenderTexture& to)
		{
			Shader::GaussianBlurH(from, internalBuffer);
			Shader::GaussianBlurV(internalBuffer, to);
		}
	}
}
