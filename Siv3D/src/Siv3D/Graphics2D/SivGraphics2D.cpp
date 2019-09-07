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

# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/Color.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>
# include <Graphics/IGraphics.hpp>

namespace s3d
{
	namespace Graphics2D
	{
		ColorF GetColorMul()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getColorMul();
		}

		ColorF GetColorAdd()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getColorAdd();
		}

		BlendState GetBlendState()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getBlendState();
		}

		RasterizerState GetRasterizerState()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getRasterizerState();
		}

		void SetSamplerState(const uint32 slot, const SamplerState& samplerState)
		{
			if (slot >= SamplerState::MaxSamplerCount)
			{
				return;
			}

			Siv3DEngine::Get<ISiv3DRenderer2D>()->setPSSamplerState(slot, samplerState);
		}

		SamplerState GetSamplerState(const uint32 slot)
		{
			if (slot >= SamplerState::MaxSamplerCount)
			{
				return SamplerState::Default2D;
			}

			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getPSSamplerState(slot);
		}

		Optional<Rect> GetViewport()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getViewport();
		}

		Optional<PixelShader> GetCustomPixelShader()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getCustomPS();
		}

		Optional<RenderTexture> GetRenderTarget()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getRT();
		}

		void SetScissorRect(const Rect& rect)
		{
			Siv3DEngine::Get<ISiv3DRenderer2D>()->setScissorRect(rect);
		}

		Rect GetScissorRect()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getScissorRect();
		}

		void SetLocalTransform(const Mat3x2& transform)
		{
			Siv3DEngine::Get<ISiv3DRenderer2D>()->setLocalTransform(transform);
		}

		const Mat3x2& GetLocalTransform()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getLocalTransform();
		}

		void SetCameraTransform(const Mat3x2& transform)
		{
			Siv3DEngine::Get<ISiv3DRenderer2D>()->setCameraTransform(transform);
		}

		const Mat3x2& GetCameraTransform()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getCameraTransform();
		}

		double GetMaxScaling()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getMaxScaling();
		}

		void SetSDFParameters(const Float4& parameters)
		{
			Siv3DEngine::Get<ISiv3DRenderer2D>()->setSDFParameters(parameters);
		}

		Float4 GetSDFParameters()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getSDFParameters();
		}

		void SetTexture(const uint32 slot, const Optional<Texture>& texture)
		{
			if (slot >= SamplerState::MaxSamplerCount)
			{
				return;
			}

			Siv3DEngine::Get<ISiv3DRenderer2D>()->setPSTexture(slot, texture);
		}

		void Flush()
		{
			Siv3DEngine::Get<ISiv3DRenderer2D>()->flush();
		}

		namespace Internal
		{
			void SetColorMul(const ColorF& color)
			{
				Siv3DEngine::Get<ISiv3DRenderer2D>()->setColorMul(color.toFloat4());
			}

			void SetColorAdd(const ColorF& color)
			{
				Siv3DEngine::Get<ISiv3DRenderer2D>()->setColorAdd(color.toFloat4());
			}

			void SetBlendState(const BlendState& blendState)
			{
				Siv3DEngine::Get<ISiv3DRenderer2D>()->setBlendState(blendState);
			}

			void SetRasterizerState(const RasterizerState& rasterizerState)
			{
				Siv3DEngine::Get<ISiv3DRenderer2D>()->setRasterizerState(rasterizerState);
			}

			void SetSamplerState(const SamplerState& samplerState)
			{
				s3d::Graphics2D::SetSamplerState(0, samplerState);
			}

			void SetViewport(const Optional<Rect>& viewport)
			{
				Siv3DEngine::Get<ISiv3DRenderer2D>()->setViewport(viewport);
			}

			void SetCustomPixelShader(const Optional<PixelShader>& ps)
			{
				Siv3DEngine::Get<ISiv3DRenderer2D>()->setCustomPS(ps);
			}

			void SetConstantBuffer(const ShaderStage stage, const uint32 index, const detail::ConstantBufferBase& buffer, const float* data, const uint32 num_vectors)
			{
				Siv3DEngine::Get<ISiv3DRenderer2D>()->setConstant(stage, index, buffer, data, num_vectors);
			}

			void SetRenderTarget(const Optional<RenderTexture>& rt)
			{
				Siv3DEngine::Get<ISiv3DRenderer2D>()->setRT(rt);
			}
		}
	}
}
