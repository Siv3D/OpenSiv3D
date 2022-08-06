//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/FloatQuad.hpp>
# include <Siv3D/TriangleIndex.hpp>
# include <Siv3D/ColorHSV.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/LineStyle.hpp>
# include <Siv3D/YesNo.hpp>
# include <Siv3D/PredefinedYesNo.hpp>
# include <Siv3D/Particle2D.hpp>
# include <Siv3D/ParticleSystem2DParameters.hpp>
# include "Vertex2DBufferPointer.hpp"

namespace s3d
{
	using BufferCreatorFunc = std::function<Vertex2DBufferPointer(Vertex2D::IndexType, Vertex2D::IndexType)>;

	namespace Vertex2DBuilder
	{
		[[nodiscard]]
		Vertex2D::IndexType BuildLine(const LineStyle& style, const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildCappedLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]);

		[[nodiscard]]
		Vertex2D::IndexType BuildUncappedLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]);

		[[nodiscard]]
		Vertex2D::IndexType BuildUncappedLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], float& startAngle);

		[[nodiscard]]
		Vertex2D::IndexType BuildSquareDotLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], float dotOffset, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildRoundDotLine(const BufferCreatorFunc& bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], float dotOffset, bool hasAlignedDot);

		[[nodiscard]]
		Vertex2D::IndexType BuildTriangle(const BufferCreatorFunc& bufferCreator, const Float2(&points)[3], const Float4& color);

		[[nodiscard]]
		Vertex2D::IndexType BuildTriangle(const BufferCreatorFunc& bufferCreator, const Float2(&points)[3], const Float4(&colors)[3]);

		[[nodiscard]]
		Vertex2D::IndexType BuildRect(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, const Float4& color);

		[[nodiscard]]
		Vertex2D::IndexType BuildRect(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, const Float4(&colors)[4]);

		[[nodiscard]]
		Vertex2D::IndexType BuildRectFrame(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, float thickness, const Float4& innerColor, const Float4& outerColor);

		[[nodiscard]]
		Vertex2D::IndexType BuildCircle(const BufferCreatorFunc& bufferCreator, const Float2& center, float r, const Float4& innerColor, const Float4& outerColor, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildCircleFrame(const BufferCreatorFunc& bufferCreator, const Float2& center, float rInner, float thickness, const Float4& innerColor, const Float4& outerColor, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildCirclePie(const BufferCreatorFunc& bufferCreator, const Float2& center, float r, float startAngle, float angle, const Float4& innerColor, const Float4& outerColor, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildCircleArc(const BufferCreatorFunc& bufferCreator, const LineStyle& style, const Float2& center, float rInner, float startAngle, float angle, float thickness, const Float4& innerColor, const Float4& outerColor, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildUncappedCircleArc(const BufferCreatorFunc& bufferCreator, const Float2& center, float rInner, float startAngle, float angle, float thickness, const Float4& innerColor, const Float4& outerColor, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildEllipse(const BufferCreatorFunc& bufferCreator, const Float2& center, float a, float b, const Float4& innerColor, const Float4& outerColor, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildEllipseFrame(const BufferCreatorFunc& bufferCreator, const Float2& center, float aInner, float bInner, float thickness, const Float4& innerColor, const Float4& outerColor, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildQuad(const BufferCreatorFunc& bufferCreator, const FloatQuad& quad, const Float4 color);

		[[nodiscard]]
		Vertex2D::IndexType BuildQuad(const BufferCreatorFunc& bufferCreator, const FloatQuad& quad, const Float4(&colors)[4]);

		[[nodiscard]]
		Vertex2D::IndexType BuildRoundRect(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const FloatRect& rect, float w, float h, float r, const Float4& color, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildRoundRectFrame(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const RoundRect& inner, const RoundRect& outer, const Float4& color, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildLineString(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const LineStyle& style, const Vec2* points, size_t size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, CloseRing closeRing, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildClosedLineString(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const Vec2* points, size_t size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildCappedLineString(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const Vec2* points, size_t size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildUncappedLineString(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const Vec2* points, size_t size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, float scale, float* startAngle0, float* startAngle1);

		[[nodiscard]]
		Vertex2D::IndexType BuildDefaultLineString(const BufferCreatorFunc& bufferCreator, const Vec2* points, const ColorF* colors, size_t size, const Optional<Float2>& offset, float thickness, bool inner, CloseRing closeRing, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildPolygon(const BufferCreatorFunc& bufferCreator, const Array<Float2>& vertices, const Array<TriangleIndex>& tirnagleIndices, const Optional<Float2>& offset, const Float4& color);

		[[nodiscard]]
		Vertex2D::IndexType BuildPolygon(const BufferCreatorFunc& bufferCreator, const Vertex2D* vertices, size_t vertexCount, const TriangleIndex* indices, size_t num_triangles);

		[[nodiscard]]
		Vertex2D::IndexType BuildPolygonTransformed(const BufferCreatorFunc& bufferCreator, const Array<Float2>& vertices, const Array<TriangleIndex>& tirnagleIndices, float s, float c, const Float2& offset, const Float4& color);

		[[nodiscard]]
		Vertex2D::IndexType BuildPolygonFrame(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const Float2* points, size_t size, float thickness, const Float4& color, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildTextureRegion(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, const FloatRect& uv, const Float4& color);

		[[nodiscard]]
		Vertex2D::IndexType BuildTextureRegion(const BufferCreatorFunc& bufferCreator, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4]);

		[[nodiscard]]
		Vertex2D::IndexType BuildTexturedCircle(const BufferCreatorFunc& bufferCreator, const Circle& circle, const FloatRect& uv, const Float4& color, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildTexturedQuad(const BufferCreatorFunc& bufferCreator, const FloatQuad& quad, const FloatRect& uv, const Float4& color);

		[[nodiscard]]
		Vertex2D::IndexType BuildTexturedRoundRect(const BufferCreatorFunc& bufferCreator, Array<Float2>& buffer, const FloatRect& rect, float w, float h, float r, const FloatRect& uvRect, const Float4& color, float scale);

		[[nodiscard]]
		Vertex2D::IndexType BuildTexturedVertices(const BufferCreatorFunc& bufferCreator, const Vertex2D* vertices, size_t vertexCount, const TriangleIndex* indices, size_t num_triangles);

		[[nodiscard]]
		Vertex2D::IndexType BuildTexturedParticles(const BufferCreatorFunc& bufferCreator, const Array<Particle2D>& particles,
			const ParticleSystem2DParameters::SizeOverLifeTimeFunc& sizeOverLifeTimeFunc, const ParticleSystem2DParameters::ColorOverLifeTimeFunc& colorOverLifeTimeFunc);
	}
}
