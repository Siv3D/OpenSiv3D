//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Renderer/D3D11/CRenderer_D3D11.hpp>
# include <Siv3D/Shader/D3D11/CShader_D3D11.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/ConstantBuffer.hpp>
# include "D3D11Renderer2DCommand.hpp"
# include "D3D11Vertex2DBatch.hpp"

namespace s3d
{
	struct D3D11StandardVS2D
	{
		VertexShader sprite;
		VertexShader fullscreen_triangle;

		bool ok() const
		{
			return sprite
				&& fullscreen_triangle;
		}
	};

	struct D3D11StandardPS2D
	{
		PixelShader shape;
		PixelShader fullscreen_triangle;

		bool ok() const
		{
			return shape
				&& fullscreen_triangle;
		}
	};

	struct D3D11VSConstants2D
	{
		Float4 transform[2];

		Float4 colorMul{ 1.0f, 1.0f, 1.0f, 1.0f };
	};

	struct D3D11PSConstants2D
	{
		Float4 colorAdd{ 0, 0, 0, 0 };

		Float4 sdfParam{ 0, 0, 0, 0 };

		Float4 internalParam{ 0, 0, 0, 0 };
	};

	class CRenderer2D_D3D11 final : public ISiv3DRenderer2D
	{
	private:

		CRenderer_D3D11* pRenderer		= nullptr;
		CShader_D3D11* pShader			= nullptr;
		ID3D11Device* m_device			= nullptr;
		ID3D11DeviceContext* m_context	= nullptr;

		std::unique_ptr<D3D11StandardVS2D> m_standardVS;
		std::unique_ptr<D3D11StandardPS2D> m_standardPS;

		ConstantBuffer<D3D11VSConstants2D> m_vsConstants2D;
		ConstantBuffer<D3D11PSConstants2D> m_psConstants2D;

		ComPtr<ID3D11InputLayout> m_inputLayout;

		D3D11Vertex2DBatch m_batches;
		D3D11Renderer2DCommandManager m_commandManager;
		BufferCreatorFunc m_bufferCreator;

	public:

		CRenderer2D_D3D11();

		~CRenderer2D_D3D11() override;

		void init() override;

		void addRect(const FloatRect& rect, const Float4& color) override;

		void flush();

		void drawFullScreenTriangle(TextureFilter textureFilter);
	};
}
