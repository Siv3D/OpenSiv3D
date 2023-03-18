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

# include <Siv3D/Graphics3D.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/BasicCamera3D.hpp>
# include <Siv3D/Renderer3D/IRenderer3D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Graphics3D
	{
		BlendState GetBlendState()
		{
			return SIV3D_ENGINE(Renderer3D)->getBlendState();
		}

		RasterizerState GetRasterizerState()
		{
			return SIV3D_ENGINE(Renderer3D)->getRasterizerState();
		}

		DepthStencilState GetDepthStencilState()
		{
			return SIV3D_ENGINE(Renderer3D)->getDepthStencilState();
		}

		SamplerState GetSamplerState(const ShaderStage shaderStage, const uint32 slot)
		{
			if (SamplerState::MaxSamplerCount <= slot)
			{
				return SamplerState::Default3D;
			}

			return SIV3D_ENGINE(Renderer3D)->getSamplerState(shaderStage, slot);
		}

		void SetScissorRect(const Rect& rect)
		{
			SIV3D_ENGINE(Renderer3D)->setScissorRect(rect);
		}

		Rect GetScissorRect()
		{
			return SIV3D_ENGINE(Renderer3D)->getScissorRect();
		}

		Optional<Rect> GetViewport()
		{
			return SIV3D_ENGINE(Renderer3D)->getViewport();
		}

		Optional<VertexShader> GetCustomVertexShader()
		{
			return SIV3D_ENGINE(Renderer3D)->getCustomVS();
		}

		Optional<PixelShader> GetCustomPixelShader()
		{
			return SIV3D_ENGINE(Renderer3D)->getCustomPS();
		}

		void SetCameraTransform(const Mat4x4& matrix, const Float3& eyePosition)
		{
			SIV3D_ENGINE(Renderer3D)->setCameraTransform(matrix, eyePosition);
		}

		void SetCameraTransform(const BasicCamera3D& camera3D)
		{
			SIV3D_ENGINE(Renderer3D)->setCameraTransform(camera3D.getMat4x4(), camera3D.getEyePosition());
		}

		const Mat4x4& GetCameraTransform()
		{
			return SIV3D_ENGINE(Renderer3D)->getCameraTransform();
		}

		Float3 GetEyePosition()
		{
			return SIV3D_ENGINE(Renderer3D)->getEyePosition();
		}

		const Mat4x4& GetLocalTransform()
		{
			return SIV3D_ENGINE(Renderer3D)->getLocalTransform();
		}

		Optional<RenderTexture> GetRenderTarget()
		{
			return SIV3D_ENGINE(Renderer3D)->getRenderTarget();
		}

		Size GetRenderTargetSize()
		{
			if (const auto rt = SIV3D_ENGINE(Renderer3D)->getRenderTarget())
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

			SIV3D_ENGINE(Renderer3D)->setVSTexture(slot, texture);
		}

		void SetPSTexture(const uint32 slot, const Optional<Texture>& texture)
		{
			if (SamplerState::MaxSamplerCount <= slot)
			{
				return;
			}

			SIV3D_ENGINE(Renderer3D)->setPSTexture(slot, texture);
		}

		void SetGlobalAmbientColor(const ColorF& color)
		{
			SIV3D_ENGINE(Renderer3D)->setGlobalAmbientColor(color.rgb());
		}

		ColorF GetGlobalAmbientColor()
		{
			return ColorF{ SIV3D_ENGINE(Renderer3D)->getGlobalAmbientColor(), 1.0 };
		}

		void SetSunDirection(const Vec3& direction)
		{
			if (direction.isZero())
			{
				throw Error{ U"Graphics3D::SetSunDirection(): direction is a zero vector" };
			}

			SIV3D_ENGINE(Renderer3D)->setSunDirection(direction.normalized());
		}

		Vec3 GetSunDirection()
		{
			return SIV3D_ENGINE(Renderer3D)->getSunDirection();
		}

		void SetSunColor(const ColorF& color)
		{
			SIV3D_ENGINE(Renderer3D)->setSunColor(color.rgb());
		}

		ColorF GetSunColor()
		{
			return ColorF{ SIV3D_ENGINE(Renderer3D)->getSunColor(), 1.0 };
		}

		void Flush()
		{
			SIV3D_ENGINE(Renderer3D)->flush();
		}

		namespace Internal
		{
			void SetBlendState(const BlendState& blendState)
			{
				SIV3D_ENGINE(Renderer3D)->setBlendState(blendState);
			}

			void SetRasterizerState(const RasterizerState& rasterizerState)
			{
				SIV3D_ENGINE(Renderer3D)->setRasterizerState(rasterizerState);
			}

			void SetDepthStencilState(const DepthStencilState& depthStencilState)
			{
				SIV3D_ENGINE(Renderer3D)->setDepthStencilState(depthStencilState);
			}

			void SetSamplerState(const ShaderStage shaderStage, const uint32 slot, const SamplerState& samplerState)
			{
				if (SamplerState::MaxSamplerCount <= slot)
				{
					return;
				}

				SIV3D_ENGINE(Renderer3D)->setSamplerState(shaderStage, slot, samplerState);
			}

			void SetViewport(const Optional<Rect>& viewport)
			{
				SIV3D_ENGINE(Renderer3D)->setViewport(viewport);
			}

			void SetLocalTransform(const Mat4x4& matrix)
			{
				SIV3D_ENGINE(Renderer3D)->setLocalTransform(matrix);
			}

			void SetCustomVertexShader(const Optional<VertexShader>& vs)
			{
				SIV3D_ENGINE(Renderer3D)->setCustomVS(vs);
			}

			void SetCustomPixelShader(const Optional<PixelShader>& ps)
			{
				SIV3D_ENGINE(Renderer3D)->setCustomPS(ps);
			}

			void SetRenderTarget(const Optional<RenderTexture>& rt)
			{
				SIV3D_ENGINE(Renderer3D)->setRenderTarget(rt);
			}

			void SetConstantBuffer(const ShaderStage stage, const uint32 slot, const ConstantBufferBase& buffer, const float* data, const uint32 num_vectors)
			{
				SIV3D_ENGINE(Renderer3D)->setConstantBuffer(stage, slot, buffer, data, num_vectors);
			}
		}
	}
}
