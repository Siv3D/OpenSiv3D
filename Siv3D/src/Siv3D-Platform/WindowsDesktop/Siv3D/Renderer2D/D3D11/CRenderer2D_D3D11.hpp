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
# include <Siv3D/Renderer2D/Vertex2DBuilder.hpp>
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

		void addLine(const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]) override;

		void addTriangle(const Float2(&points)[3], const Float4& color) override;

		void addTriangle(const Float2(&points)[3], const Float4(&colors)[3]) override;

		void addRect(const FloatRect& rect, const Float4& color) override;

		void addRect(const FloatRect& rect, const Float4(&colors)[4]) override;

		void addRectFrame(const FloatRect& rect, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addCircle(const Float2& center, float r, const Float4& innerColor, const Float4& outerColor) override;

		void addCircleFrame(const Float2& center, float rInner, float thickness, const Float4& innerColor, const Float4& outerColor) override;

		void addQuad(const FloatQuad& quad, const Float4& color) override;

		void addQuad(const FloatQuad& quad, const Float4(&colors)[4]) override;

		void addLineString(const Vec2* points, size_t size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, IsClosed isClosed) override;

		void addPolygon(const Array<Float2>& vertices, const Array<TriangleIndex>& indices, const Optional<Float2>& offset, const Float4& color) override;

		void addPolygon(const Vertex2D* vertices, size_t vertexCount, const TriangleIndex* indices, size_t num_triangles) override;

		float getMaxScaling() const noexcept override;

		void flush();

		void drawFullScreenTriangle(TextureFilter textureFilter);
	};
}
