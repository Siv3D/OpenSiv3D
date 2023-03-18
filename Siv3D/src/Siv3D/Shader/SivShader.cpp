//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Shader.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/ScopedCustomShader2D.hpp>
# include <Siv3D/ScopedRenderTarget2D.hpp>
# include <Siv3D/ScopedRenderStates2D.hpp>

namespace s3d
{
	namespace Shader
	{
		void Copy(const TextureRegion& from, const RenderTexture& to)
		{
			if (not from.texture)
			{
				throw Error{ U"Shader::Copy(): from.texture is empty" };
			}

			if (not to)
			{
				throw Error{ U"Shader::Copy(): to is empty" };
			}

			if (from.size != to.size())
			{
				throw Error{ U"Shader::Copy(): from.size != to.size()" };
			}

			if (from.texture == to)
			{
				throw Error{ U"Shader::Copy(): from.texture == to" };
			}

			const ScopedRenderTarget2D target{ to };
			const ScopedRenderStates2D states{ BlendState::Opaque, SamplerState::ClampNearest, RasterizerState::Default2D };
			const ScopedCustomShader2D shader{ SIV3D_ENGINE(Shader)->getEnginePS(EnginePS::Copy) };
			from.draw();
		}

		void Downsample(const TextureRegion& from, const RenderTexture& to)
		{
			if (not from.texture)
			{
				throw Error{ U"Shader::DownSample(): from.texture is empty" };
			}

			if (not to)
			{
				throw Error{ U"Shader::DownSample(): to is empty" };
			}

			if (from.texture == to)
			{
				throw Error{ U"Shader::DownSample(): from.texture == to" };
			}

			const ScopedRenderTarget2D target{ to };
			const ScopedRenderStates2D states{ BlendState::Opaque, SamplerState::ClampLinear, RasterizerState::Default2D };
			const ScopedCustomShader2D shader{ SIV3D_ENGINE(Shader)->getEnginePS(EnginePS::Copy) };
			from.resized(to.size()).draw();
		}

		void GaussianBlurH(const TextureRegion& from, const RenderTexture& to)
		{
			GaussianBlur(from, to, Vec2{ 1, 0 });
		}

		void GaussianBlurV(const TextureRegion& from, const RenderTexture& to)
		{
			GaussianBlur(from, to, Vec2{ 0, 1 });
		}

		void GaussianBlur(const TextureRegion& from, const RenderTexture& to, const Vec2& direction)
		{
			if (not from.texture)
			{
				throw Error{ U"Shader::GaussianBlur(): from.texture is empty" };
			}

			if (not to)
			{
				throw Error{ U"Shader::GaussianBlur(): to is empty" };
			}

			if (from.size != to.size())
			{
				throw Error{ U"Shader::GaussianBlur(): from.size != to.size()" };
			}

			if (from.texture == to)
			{
				throw Error{ U"Shader::GaussianBlur(): from.texture == to" };
			}

			const ScopedRenderTarget2D target{ to };
			const ScopedRenderStates2D states{ BlendState::Opaque, SamplerState::ClampLinear, RasterizerState::Default2D };
			const ScopedCustomShader2D shader{ SIV3D_ENGINE(Shader)->getEnginePS(EnginePS::GaussianBlur_9) };
			Graphics2D::Internal::SetInternalPSConstants(Float4{ Float2{ 1, 1 } / from.size * Float2{ from.uvRect.right - from.uvRect.left, from.uvRect.bottom - from.uvRect.top }, direction });
			from.draw();
		}

		void GaussianBlur(const TextureRegion& from, const RenderTexture& internalBuffer, const RenderTexture& to)
		{
			Shader::GaussianBlurH(from, internalBuffer);
			Shader::GaussianBlurV(internalBuffer, to);
		}

		void LinearToScreen(const TextureRegion& src, const TextureFilter textureFilter, const RectF& dst)
		{
			LinearToScreen(src, dst, textureFilter);
		}

		void LinearToScreen(const TextureRegion& src, const Vec2& pos, const TextureFilter textureFilter)
		{
			LinearToScreen(src, RectF{ pos, src.size }, textureFilter);
		}

		void LinearToScreen(const TextureRegion& src, const RectF& dst, const TextureFilter textureFilter)
		{
			const Vec2 pos = dst.pos;
			const Vec2 scale = (dst.size / src.size);
			const ScopedCustomShader2D shader{ SIV3D_ENGINE(Shader)->getEnginePS(EnginePS::ApplySrgbCurve) };
			BlendState bs = BlendState::Opaque;
			bs.writeA = false;

			if (scale == Vec2::One())
			{
				const ScopedRenderStates2D rs{ bs, SamplerState::ClampNearest, RasterizerState::Default2D };
				src.draw(pos);
			}
			else
			{
				const SamplerState samplerState = ((textureFilter == TextureFilter::Nearest) ? SamplerState::ClampNearest : SamplerState::ClampLinear);
				const ScopedRenderStates2D rs{ bs, samplerState, RasterizerState::Default2D };
				src.scaled(scale).draw(pos);
			}
			
			Graphics2D::Flush();
		}
	}
}
