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

# include <Siv3D/Circle.hpp>
# include <Siv3D/Ellipse.hpp>
# include <Siv3D/Geometry2D.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/TexturedCircle.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/Sprite.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	Circle::Circle(const position_type& p0, const position_type& p1, const position_type& p2) noexcept
	{
		if (p0 == p1)
		{
			*this = Circle(p0, p2);
			return;
		}
		else if (p0 == p2 || p1 == p2)
		{
			*this = Circle(p0, p1);
			return;
		}

		const double a02 = 2 * (p0.x - p2.x);
		const double b02 = 2 * (p0.y - p2.y);
		const double c02 = (p0.y * p0.y - p2.y * p2.y) + (p0.x * p0.x - p2.x * p2.x);
		const double a12 = 2 * (p1.x - p2.x);
		const double b12 = 2 * (p1.y - p2.y);
		const double c12 = (p1.y * p1.y - p2.y * p2.y) + (p1.x * p1.x - p2.x * p2.x);
		const double cy = (a02 * c12 - a12 * c02) / (a02 * b12 - a12 * b02);
		const double cx = std::abs(a02) < std::abs(a12) ? ((c12 - b12 * cy) / a12) : ((c02 - b02 * cy) / a02);
		*this = Circle(cx, cy, p0.distanceFrom(cx, cy));
	}

	Ellipse Circle::stretched(const double _x, const double _y) const noexcept
	{
		return Ellipse(center, r + _x, r + _y);
	}

	Ellipse Circle::scaled(const double sx, const double sy) const noexcept
	{
		return Ellipse(center, r * sx, r * sy);
	}

	Optional<Array<Vec2>> Circle::intersectsAt(const Line& line) const
	{
		return Geometry2D::IntersectAt(line, Ellipse(*this));
	}

	Optional<Array<Vec2>> Circle::intersectsAt(const Rect& rect) const
	{
		return Geometry2D::IntersectAt(rect, Ellipse(*this));
	}

	Optional<Array<Vec2>> Circle::intersectsAt(const RectF& rect) const
	{
		return Geometry2D::IntersectAt(rect, Ellipse(*this));
	}

	bool Circle::leftClicked() const
	{
		return MouseL.down() && mouseOver();
	}

	bool Circle::leftPressed() const
	{
		return MouseL.pressed() && mouseOver();
	}

	bool Circle::leftReleased() const
	{
		return MouseL.up() && mouseOver();
	}

	bool Circle::rightClicked() const
	{
		return MouseR.down() && mouseOver();
	}

	bool Circle::rightPressed() const
	{
		return MouseR.pressed() && mouseOver();
	}

	bool Circle::rightReleased() const
	{
		return MouseR.up() && mouseOver();
	}

	bool Circle::mouseOver() const
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	const Circle& Circle::draw(const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addCircle(
			center,
			static_cast<float>(r),
			color.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawFrame(double innerThickness, double outerThickness, const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addCircleFrame(
			center,
			static_cast<float>(r - innerThickness),
			static_cast<float>(innerThickness + outerThickness),
			color.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawFrame(double innerThickness, double outerThickness, const ColorF& innerColor, const ColorF& outerColor) const
	{
		Siv3DEngine::GetRenderer2D()->addCircleFrame(
			center,
			static_cast<float>(r - innerThickness),
			static_cast<float>(innerThickness + outerThickness),
			innerColor.toFloat4(),
			outerColor.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawPie(double startAngle, double angle, const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addCirclePie(
			center,
			static_cast<float>(r),
			static_cast<float>(startAngle),
			static_cast<float>(angle),
			color.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawArc(double startAngle, double angle, double innerThickness, double outerThickness, const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addCircleArc(
			center,
			static_cast<float>(r - innerThickness),
			static_cast<float>(startAngle),
			static_cast<float>(angle),
			static_cast<float>(innerThickness + outerThickness),
			color.toFloat4()
		);

		return *this;
	}

	const Circle& Circle::drawShadow(const Vec2& offset, double blurRadius, double spread, const ColorF& color) const
	{
		if (blurRadius < 0.0)
		{
			return *this;
		}

		if (blurRadius * 0.5 > (r + spread))
		{
			blurRadius = (r + spread) * 2.0;
		}

		const float absR = std::abs(static_cast<float>(r + spread));
		const float inShadowR = static_cast<float>(r + spread - blurRadius * 0.5);
		const float shadowR = absR + static_cast<float>(blurRadius * 0.5);
		const float scaledShadowR = shadowR;
		const float centerX = static_cast<float>(center.x + offset.x);
		const float centerY = static_cast<float>(center.y + offset.y);
		const Float4 colorF = color.toFloat4();

		const uint32 quality = static_cast<uint32>(Min(scaledShadowR * 0.225f + 18.0f, 255.0f));

		const uint32 outerVertexSize = quality;
		const uint32 innnerVertexSize = quality;

		const uint32 outerIndexSize = quality * 6;
		const uint32 innnerIndexSize = quality * 3;

		const uint32 vertexSize = outerVertexSize + innnerVertexSize + 1;
		const uint32 indexSize = outerIndexSize + innnerIndexSize;

		Sprite sprite(vertexSize, indexSize);

		const float radDelta = Math::TwoPiF / quality;

		for (uint32 i = 0; i < quality; ++i)
		{
			const float rad = radDelta * i;
			const float c = std::cos(rad);
			const float s = std::sin(rad);
			
			Vertex2D* inner = &sprite.vertices[i];
			Vertex2D* outer = inner + outerVertexSize;
			
			inner->pos.set(centerX + shadowR * c, centerY - shadowR * s);
			inner->tex.set(0.5f, 0.0f);
			inner->color = colorF;

			outer->pos.set(centerX + inShadowR * c, centerY - inShadowR * s);
			outer->tex.set(0.5f, 0.5f);
			outer->color = colorF;
		}

		{
			Vertex2D* v = &sprite.vertices[vertexSize - 1];
			v->pos.set(centerX, centerY);
			v->tex.set(0.5f, 0.5f);
			v->color = colorF;
		}

		for (uint32 i = 0; i < quality; ++i)
		{
			sprite.indices[i * 6 + 0] = i % (outerVertexSize);
			sprite.indices[i * 6 + 1] = (i + 1) % (outerVertexSize);
			sprite.indices[i * 6 + 2] = (i + outerVertexSize) % (outerVertexSize * 2);
			sprite.indices[i * 6 + 3] = (i + outerVertexSize) % (outerVertexSize * 2);
			sprite.indices[i * 6 + 4] = (i + 1) % (outerVertexSize);
			sprite.indices[i * 6 + 5] = (i + 1) % (outerVertexSize)+outerVertexSize;
		}

		for (uint32 i = 0; i < quality; ++i)
		{
			sprite.indices[outerIndexSize + i * 3 + 0] = outerVertexSize + (i + 0);
			sprite.indices[outerIndexSize + i * 3 + 1] = vertexSize - 1;
			sprite.indices[outerIndexSize + i * 3 + 2] = outerVertexSize + (i + 1) % quality;
		}

		sprite.draw(Siv3DEngine::GetRenderer2D()->getBoxShadowTexture());

		return *this;
	}

	TexturedCircle Circle::operator ()(const Texture& texture) const
	{
		return TexturedCircle(texture,
			0.0f, 0.0f, 1.0f, 1.0f,
			*this);
	}

	TexturedCircle Circle::operator ()(const TextureRegion& textureRegion) const
	{
		return TexturedCircle(textureRegion.texture,
			textureRegion.uvRect,
			*this);
	}
}
