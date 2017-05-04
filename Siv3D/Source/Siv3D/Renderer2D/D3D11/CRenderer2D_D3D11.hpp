//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <wrl.h>
using namespace Microsoft::WRL;
# include <d3d11.h>
# include <d3dcompiler.h>
# include "../IRenderer2D.hpp"
# include "D3D11SpriteBatch.hpp"
# include "D3D11Renderer2DCommandManager.hpp"

namespace s3d
{
	class CRenderer2D_D3D11 : public ISiv3DRenderer2D
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		ComPtr<ID3D11InputLayout> m_inputLayout;

		D3D11SpriteBatch m_spriteBatch;

		ComPtr<ID3D11Buffer> m_cbuffer;

		D3D11Render2DCommandManager m_commandManager;

	public:

		CRenderer2D_D3D11();

		~CRenderer2D_D3D11() override;

		bool init(ID3D11Device* device, ID3D11DeviceContext* context);

		void flush() override;

		void addTriangle(const Float2(&pts)[3], const Float4& color) override;

		void addTriangle(const Float2(&pts)[3], const Float4(&colors)[3]) override;

		void addRect(const FloatRect& rect, const Float4& color) override;

		void addRect(const FloatRect& rect, const Float4(&colors)[4]) override;

		void addRectFrame(const FloatRect& rect, float thickness, const Float4& color) override;

		void addCircle(const Float2& center, float r, const Float4& color) override;

		void addCircleFrame(const Float2& center, float r, float thickness, const Float4& color) override;

		void addCircleFrame(const Float2& center, float r, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addQuad(const FloatQuad& quad, const Float4& color) override;

		void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) override;
	};
}

# endif
