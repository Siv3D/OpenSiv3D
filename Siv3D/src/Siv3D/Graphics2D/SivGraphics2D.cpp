//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/Shader.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	namespace Graphics2D
	{
		void SetBlendState(const BlendState& blendState)
		{
			Siv3DEngine::GetRenderer2D()->setBlendState(blendState);
		}

		BlendState GetBlendState()
		{
			return Siv3DEngine::GetRenderer2D()->getBlendState();
		}

		void SetRasterizerState(const RasterizerState& rasterizerState)
		{
			Siv3DEngine::GetRenderer2D()->setRasterizerState(rasterizerState);
		}

		RasterizerState GetRasterizerState()
		{
			return Siv3DEngine::GetRenderer2D()->getRasterizerState();
		}

		void SetSamplerState(const uint32 slot, const SamplerState& samplerState)
		{
			Siv3DEngine::GetRenderer2D()->setSamplerState(ShaderStage::Pixel, slot, samplerState);
		}

		SamplerState GetSamplerState(const uint32 slot)
		{
			return Siv3DEngine::GetRenderer2D()->getSamplerStates(ShaderStage::Pixel)[slot];
		}

		void SetScissorRect(const Rect& rect)
		{
			Siv3DEngine::GetRenderer2D()->setScissorRect(rect);
		}

		Rect GetScissorRect()
		{
			return Siv3DEngine::GetRenderer2D()->getScissorRect();
		}


		void SetViewport(const Optional<Rect>& viewport)
		{
			Siv3DEngine::GetRenderer2D()->setViewport(viewport);
		}

		Optional<Rect> GetViewport()
		{
			return Siv3DEngine::GetRenderer2D()->getViewport();
		}
		
		void SetTransformLocal(const Mat3x2& matrix)
		{
			Siv3DEngine::GetRenderer2D()->setTransformLocal(matrix);
		}

		void SetTransformCamera(const Mat3x2& matrix)
		{
			Siv3DEngine::GetRenderer2D()->setTransformCamera(matrix);
		}

		void SetTransformScreen(const Mat3x2& matrix)
		{
			Siv3DEngine::GetRenderer2D()->setTransformScreen(matrix);
		}
		
		const Mat3x2& GetTransformLocal()
		{
			return Siv3DEngine::GetRenderer2D()->getTransformLocal();
		}

		const Mat3x2& GetTransformCamera()
		{
			return Siv3DEngine::GetRenderer2D()->getTransformCamera();
		}

		const Mat3x2& GetTransformScreen()
		{
			return Siv3DEngine::GetRenderer2D()->getTransformScreen();
		}
	}
}
