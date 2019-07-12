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

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Particle2D.hpp>
# include <Siv3D/ParticleSystem2D.hpp>

namespace s3d
{
	using IndexType = Vertex2D::IndexType;

	using BufferCreatorFunc = std::function<std::tuple<Vertex2D*, IndexType*, IndexType>(IndexType, IndexType)>;

	namespace Vertex2DBuilder
	{
		[[nodiscard]] uint16 BuildSquareCappedLine(BufferCreatorFunc bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]);

		[[nodiscard]] uint16 BuildRoundCappedLine(BufferCreatorFunc bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], float& startAngle);

		[[nodiscard]] uint16 BuildUncappedLine(BufferCreatorFunc bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2]);

		[[nodiscard]] uint16 BuildSquareDotLine(BufferCreatorFunc bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], float dotOffset, float scale);

		[[nodiscard]] uint16 BuildRoundDotLine(BufferCreatorFunc bufferCreator, const Float2& begin, const Float2& end, float thickness, const Float4(&colors)[2], float dotOffset, bool hasAlignedDot);

		[[nodiscard]] uint16 BuildTriangle(BufferCreatorFunc bufferCreator, const Float2(&pts)[3], const Float4& color);

		[[nodiscard]] uint16 BuildTriangle(BufferCreatorFunc bufferCreator, const Float2(&pts)[3], const Float4(&colors)[3]);

		[[nodiscard]] uint16 BuildRect(BufferCreatorFunc bufferCreator, const FloatRect& rect, const Float4& color);

		[[nodiscard]] uint16 BuildRect(BufferCreatorFunc bufferCreator, const FloatRect& rect, const Float4(&colors)[4]);

		[[nodiscard]] uint16 BuildRectFrame(BufferCreatorFunc bufferCreator, const FloatRect& rect, float thickness, const Float4& color);

		[[nodiscard]] uint16 BuildCircle(BufferCreatorFunc bufferCreator, const Float2& center, float r, const Float4& color, float scale);

		[[nodiscard]] uint16 BuildCircleFrame(BufferCreatorFunc bufferCreator, const Float2& center, float rInner, float thickness, const Float4& innerColor, const Float4& outerColor, float scale);

		[[nodiscard]] uint16 BuildCirclePie(BufferCreatorFunc bufferCreator, const Float2& center, float r, float startAngle, float angle, const Float4& color, float scale);
	
		[[nodiscard]] uint16 BuildCircleArc(BufferCreatorFunc bufferCreator, const Float2& center, float rInner, float startAngle, float angle, float thickness, const Float4& color, float scale);

		[[nodiscard]] uint16 BuildEllipse(BufferCreatorFunc bufferCreator, const Float2& center, float a, float b, const Float4& color, float scale);

		[[nodiscard]] uint16 BuildEllipseFrame(BufferCreatorFunc bufferCreator, const Float2& center, float aInner, float bInner, float thickness, const Float4& innerColor, const Float4& outerColor, float scale);

		[[nodiscard]] uint16 BuildQuad(BufferCreatorFunc bufferCreator, const FloatQuad& quad, const Float4 color);

		[[nodiscard]] uint16 BuildQuad(BufferCreatorFunc bufferCreator, const FloatQuad& quad, const Float4(&colors)[4]);

		[[nodiscard]] uint16 BuildRoundRect(BufferCreatorFunc bufferCreator, const FloatRect& rect, float w, float h, float r, const Float4& color, float scale);

		[[nodiscard]] uint16 BuildShape2D(BufferCreatorFunc bufferCreator, const Array<Float2>& vertices, const Array<uint16>& indices, const Optional<Float2>& offset, const Float4& color);

		[[nodiscard]] uint16 BuildShape2DTransformed(BufferCreatorFunc bufferCreator, const Array<Float2>& vertices, const Array<uint16>& indices, float s, float c, const Float2& offset, const Float4& color);

		[[nodiscard]] uint16 BuildShape2DFrame(BufferCreatorFunc bufferCreator, const Float2* pts, uint16 size, float thickness, const Float4& color, float scale);

		[[nodiscard]] uint16 BuildSprite(BufferCreatorFunc bufferCreator, const Sprite& sprite, IndexType startIndex, IndexType indexCount);

		[[nodiscard]] uint16 BuildSquareCappedLineString(BufferCreatorFunc bufferCreator, const Vec2* pts, uint16 size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, bool isClosed, float scale);

		[[nodiscard]] uint16 BuildRoundCappedLineString(BufferCreatorFunc bufferCreator, const Vec2* pts, uint16 size, const Optional<Float2>& offset, float thickness, bool inner, const Float4& color, float scale, float& startAngle, float& endAngle);

		[[nodiscard]] uint16 BuildDotLineString(BufferCreatorFunc bufferCreator, const Vec2* pts, uint16 size, const Optional<Float2>& offset, float thickness, const Float4& color, bool isClosed, bool squareDot, float dotOffset, bool hasAlignedDot, float scale);

		[[nodiscard]] uint16 BuildTextureRegion(BufferCreatorFunc bufferCreator, const FloatRect& rect, const FloatRect& uv, const Float4& color);

		[[nodiscard]] uint16 BuildTextureRegion(BufferCreatorFunc bufferCreator, const FloatRect& rect, const FloatRect& uv, const Float4(&colors)[4]);
	
		[[nodiscard]] uint16 BuildTexturedCircle(BufferCreatorFunc bufferCreator, const Circle& circle, const FloatRect& uv, const Float4& color, float scale);

		[[nodiscard]] uint16 BuildTexturedQuad(BufferCreatorFunc bufferCreator, const FloatQuad& quad, const FloatRect& uv, const Float4& color);
	
		[[nodiscard]] uint16 BuildTexturedParticles(BufferCreatorFunc bufferCreator, const Array<Particle2D>& particles,
			const ParticleSystem2DParameters::SizeOverLifeTimeFunc& sizeOverLifeTimeFunc, const ParticleSystem2DParameters::ColorOverLifeTimeFunc& colorOverLifeTimeFunc);
	}
}
