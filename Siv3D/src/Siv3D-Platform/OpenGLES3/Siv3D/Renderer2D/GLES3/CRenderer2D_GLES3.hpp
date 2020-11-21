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
# include <Siv3D/ConstantBuffer.hpp>
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/TextureFilter.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Renderer2D/Vertex2DBuilder.hpp>
# include <Siv3D/Renderer2D/Renderer2DCommon.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include "GLES3Renderer2DCommand.hpp"
# include "GLES3Vertex2DBatch.hpp"

namespace s3d
{
	class CRenderer_GLES3;
	class CShader_GLES3;

	struct GLES3StandardVS2D
	{
		VertexShader sprite;
		VertexShader fullscreen_triangle;

		bool ok() const
		{
			return sprite
				&& fullscreen_triangle;
		}
	};

	struct GLES3StandardPS2D
	{
		PixelShader shape;
		PixelShader fullscreen_triangle;

		bool ok() const
		{
			return shape
				&& fullscreen_triangle;
		}
	};

	class CRenderer2D_GLES3 final : public ISiv3DRenderer2D
	{
	private:

		CRenderer_GLES3* pRenderer = nullptr;
		CShader_GLES3* pShader = nullptr;

		std::unique_ptr<GLES3StandardVS2D> m_standardVS;
		std::unique_ptr<GLES3StandardPS2D> m_standardPS;

		ConstantBuffer<VSConstants2D> m_vsConstants2D;
		ConstantBuffer<PSConstants2D> m_psConstants2D;

		GLES3Vertex2DBatch m_batches;
		GLES3Renderer2DCommandManager m_commandManager;
		BufferCreatorFunc m_bufferCreator;

		//////////////////////////////////////////////////
		//
		//	full screen triangle
		//
		//////////////////////////////////////////////////
		GLuint m_vertexArray		= 0;
		GLuint m_sampler			= 0;

	public:

		CRenderer2D_GLES3();

		~CRenderer2D_GLES3() override;

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

		void addPolygonFrame(const Float2* points, size_t size, float thickness, const Float4& color) override;

		float getMaxScaling() const noexcept override;

		void flush();

		void drawFullScreenTriangle(TextureFilter textureFilter);
	};
}
