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

# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/TextStyle.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Graphics2D
	{
		Float4 GetColorMul()
		{
			return SIV3D_ENGINE(Renderer2D)->getColorMul();
		}

		Float4 GetColorAdd()
		{
			return SIV3D_ENGINE(Renderer2D)->getColorAdd();
		}

		BlendState GetBlendState()
		{
			return SIV3D_ENGINE(Renderer2D)->getBlendState();
		}

		RasterizerState GetRasterizerState()
		{
			return SIV3D_ENGINE(Renderer2D)->getRasterizerState();
		}

		SamplerState GetSamplerState(const ShaderStage shaderStage, const uint32 slot)
		{
			if (SamplerState::MaxSamplerCount <= slot)
			{
				return SamplerState::Default2D;
			}

			return SIV3D_ENGINE(Renderer2D)->getSamplerState(shaderStage, slot);
		}

		void SetScissorRect(const Rect& rect)
		{
			SIV3D_ENGINE(Renderer2D)->setScissorRect(rect);
		}

		Rect GetScissorRect()
		{
			return SIV3D_ENGINE(Renderer2D)->getScissorRect();
		}

		Optional<Rect> GetViewport()
		{
			return SIV3D_ENGINE(Renderer2D)->getViewport();
		}

		Optional<VertexShader> GetCustomVertexShader()
		{
			return SIV3D_ENGINE(Renderer2D)->getCustomVS();
		}

		Optional<PixelShader> GetCustomPixelShader()
		{
			return SIV3D_ENGINE(Renderer2D)->getCustomPS();
		}

		const Mat3x2& GetLocalTransform()
		{
			return SIV3D_ENGINE(Renderer2D)->getLocalTransform();
		}

		const Mat3x2& GetCameraTransform()
		{
			return SIV3D_ENGINE(Renderer2D)->getCameraTransform();
		}

		float GetMaxScaling() noexcept
		{
			return SIV3D_ENGINE(Renderer2D)->getMaxScaling();
		}

		Optional<RenderTexture> GetRenderTarget()
		{
			return SIV3D_ENGINE(Renderer2D)->getRenderTarget();
		}

		Size GetRenderTargetSize()
		{
			if (const auto rt = SIV3D_ENGINE(Renderer2D)->getRenderTarget())
			{
				return rt->size();
			}
			else
			{
				return Scene::Size();
			}
		}

		void SetVSTexture(const uint32 slot, const Optional<Texture>& texture)
		{
			if (SamplerState::MaxSamplerCount <= slot)
			{
				return;
			}

			SIV3D_ENGINE(Renderer2D)->setVSTexture(slot, texture);
		}

		void SetPSTexture(const uint32 slot, const Optional<Texture>& texture)
		{
			if (SamplerState::MaxSamplerCount <= slot)
			{
				return;
			}

			SIV3D_ENGINE(Renderer2D)->setPSTexture(slot, texture);
		}

		void Flush()
		{
			SIV3D_ENGINE(Renderer2D)->flush();
		}

		void DrawTriangles(const uint32 count)
		{
			SIV3D_ENGINE(Renderer2D)->addNullVertices(count * 3);
		}

		void SetSDFParameters(const TextStyle& textStyle)
		{
			Float4 param = textStyle.param;
			param.x = (0.25f + param.x * 0.5f);
			param.y = (0.25f + param.y * 0.5f);
			Internal::SetSDFParameters({ param, textStyle.outlineColor, textStyle.shadowColor });
		}

		void SetMSDFParameters(const TextStyle& textStyle)
		{
			Internal::SetSDFParameters({ textStyle.param, textStyle.outlineColor, textStyle.shadowColor });
		}

		namespace Internal
		{
			void SetColorMul(const Float4& color)
			{
				SIV3D_ENGINE(Renderer2D)->setColorMul(color);
			}

			void SetColorAdd(const Float4& color)
			{
				SIV3D_ENGINE(Renderer2D)->setColorAdd(color);
			}

			void SetBlendState(const BlendState& blendState)
			{
				SIV3D_ENGINE(Renderer2D)->setBlendState(blendState);
			}

			void SetRasterizerState(const RasterizerState& rasterizerState)
			{
				SIV3D_ENGINE(Renderer2D)->setRasterizerState(rasterizerState);
			}

			void SetSamplerState(const ShaderStage shaderStage, const uint32 slot, const SamplerState& samplerState)
			{
				if (SamplerState::MaxSamplerCount <= slot)
				{
					return;
				}

				SIV3D_ENGINE(Renderer2D)->setSamplerState(shaderStage, slot, samplerState);
			}

			void SetViewport(const Optional<Rect>& viewport)
			{
				SIV3D_ENGINE(Renderer2D)->setViewport(viewport);
			}

			void SetSDFParameters(const std::array<Float4, 3>& params)
			{
				SIV3D_ENGINE(Renderer2D)->setSDFParameters(params);
			}

			void SetInternalPSConstants(const Float4& value)
			{
				SIV3D_ENGINE(Renderer2D)->setInternalPSConstants(value);
			}

			void SetCustomVertexShader(const Optional<VertexShader>& vs)
			{
				SIV3D_ENGINE(Renderer2D)->setCustomVS(vs);
			}

			void SetCustomPixelShader(const Optional<PixelShader>& ps)
			{
				SIV3D_ENGINE(Renderer2D)->setCustomPS(ps);
			}

			void SetLocalTransform(const Mat3x2& transform)
			{
				SIV3D_ENGINE(Renderer2D)->setLocalTransform(transform);
			}

			void SetCameraTransform(const Mat3x2& transform)
			{
				SIV3D_ENGINE(Renderer2D)->setCameraTransform(transform);
			}

			void SetRenderTarget(const Optional<RenderTexture>& rt)
			{
				SIV3D_ENGINE(Renderer2D)->setRenderTarget(rt);
			}

			void SetConstantBuffer(const ShaderStage stage, const uint32 slot, const ConstantBufferBase& buffer, const float* data, const uint32 num_vectors)
			{
				SIV3D_ENGINE(Renderer2D)->setConstantBuffer(stage, slot, buffer, data, num_vectors);
			}
		}
	}
}
