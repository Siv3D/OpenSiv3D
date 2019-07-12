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
		void SetColorMul(const ColorF& color)
		{
			Siv3DEngine::Get<ISiv3DRenderer2D>()->setColorMul(color.toFloat4());
		}

		ColorF GetColorMul()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getColorMul();
		}

		void SetColorAdd(const ColorF& color)
		{
			Siv3DEngine::Get<ISiv3DRenderer2D>()->setColorAdd(color.toFloat4());
		}

		ColorF GetColorAdd()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getColorAdd();
		}

		void SetBlendState(const BlendState& blendState)
		{
			Siv3DEngine::Get<ISiv3DRenderer2D>()->setBlendState(blendState);
		}

		BlendState GetBlendState()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getBlendState();
		}

		void SetRasterizerState(const RasterizerState& rasterizerState)
		{
			Siv3DEngine::Get<ISiv3DRenderer2D>()->setRasterizerState(rasterizerState);
		}

		RasterizerState GetRasterizerState()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getRasterizerState();
		}

		void SetSamplerState(const uint32 slot, const SamplerState& samplerState)
		{
			Siv3DEngine::Get<ISiv3DRenderer2D>()->setPSSamplerState(slot, samplerState);
		}

		void SetSamplerState(const SamplerState& samplerState)
		{
			SetSamplerState(0, samplerState);
		}

		SamplerState GetSamplerState(const uint32 slot)
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getPSSamplerState(slot);
		}

		void SetScissorRect(const Rect& rect)
		{
			Siv3DEngine::Get<ISiv3DRenderer2D>()->setScissorRect(rect);
		}

		Rect GetScissorRect()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getScissorRect();
		}

		void SetViewport(const Optional<Rect>& viewport)
		{
			Siv3DEngine::Get<ISiv3DRenderer2D>()->setViewport(viewport);
		}

		Optional<Rect> GetViewport()
		{
			return Siv3DEngine::Get<ISiv3DRenderer2D>()->getViewport();
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
	}
}
