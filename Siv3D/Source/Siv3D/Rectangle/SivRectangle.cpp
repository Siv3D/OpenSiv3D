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

# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Format.hpp>
# include <Siv3D/FloatRect.hpp>
# include <Siv3D/RoundRect.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Cursor.hpp>
# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/TexturedQuad.hpp>
# include <Siv3D/Sprite.hpp>
# include "../Siv3DEngine.hpp"
# include "../Renderer2D/IRenderer2D.hpp"

namespace s3d
{
	template <class SizeType>
	RoundRect Rectangle<SizeType>::rounded(const double r) const noexcept
	{
		return RoundRect(*this, r);
	}

	template <class SizeType>
	bool Rectangle<SizeType>::leftClicked() const
	{
		return MouseL.down() && mouseOver();
	}

	template <class SizeType>
	bool Rectangle<SizeType>::leftPressed() const
	{
		return MouseL.pressed() && mouseOver();
	}

	template <class SizeType>
	bool Rectangle<SizeType>::leftReleased() const
	{
		return MouseL.up() && mouseOver();
	}

	template <class SizeType>
	bool Rectangle<SizeType>::rightClicked() const
	{
		return MouseR.down() && mouseOver();
	}

	template <class SizeType>
	bool Rectangle<SizeType>::rightPressed() const
	{
		return MouseR.pressed() && mouseOver();
	}

	template <class SizeType>
	bool Rectangle<SizeType>::rightReleased() const
	{
		return MouseR.up() && mouseOver();
	}

	template <class SizeType>
	bool Rectangle<SizeType>::mouseOver() const
	{
		return Geometry2D::Intersect(Cursor::PosF(), *this);
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::draw(const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addRect(FloatRect(x, y, x + w, y + h), color.toFloat4());

		return *this;
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::draw(const ColorF(&colors)[4]) const
	{
		Siv3DEngine::GetRenderer2D()->addRect(FloatRect(x, y, x + w, y + h),
			{ colors[0].toFloat4(), colors[1].toFloat4(), colors[2].toFloat4(), colors[3].toFloat4() });

		return *this;
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::drawFrame(const double innerThickness, const double outerThickness, const ColorF& color) const
	{
		Siv3DEngine::GetRenderer2D()->addRectFrame(
			FloatRect(x + innerThickness, y + innerThickness, x + w - innerThickness, y + h - innerThickness),
			static_cast<float>(innerThickness + outerThickness),
			color.toFloat4()
		);

		return *this;
	}

	template <class SizeType>
	const Rectangle<SizeType>& Rectangle<SizeType>::drawShadow(const Vec2& offset, double blurRadius, double spread, const ColorF& color) const
	{
		if (blurRadius < 0.0)
		{
			return *this;
		}

		const RectF rect = RectF(pos + offset, size).stretched(spread + blurRadius * 0.5);
		const Float4 colorF = color.toFloat4();

		const double rr = Min({ rect.w * 0.5, rect.h * 0.5, blurRadius });
		const float xs[4] =
		{
			static_cast<float>(rect.x),
			static_cast<float>(rect.x + rr),
			static_cast<float>(rect.x + rect.w - rr),
			static_cast<float>(rect.x + rect.w)
		};

		const float ys[4] =
		{
			static_cast<float>(rect.y),
			static_cast<float>(rect.y + rr),
			static_cast<float>(rect.y + rect.h - rr),
			static_cast<float>(rect.y + rect.h)
		};

		const float uvs[4] = { 0.0f, 0.5f, 0.5f, 1.0f };

		Sprite sprite(16, 54);

		Vertex2D* pVertex = sprite.vertices.data();

		for (int32 i = 0; i < 16; ++i)
		{
			pVertex->pos.set(xs[i % 4], ys[i / 4]);
			pVertex->tex.set(uvs[i % 4], uvs[i / 4]);
			pVertex->color = colorF;
			++pVertex;
		}

		static const uint32 rectIndexTable[6] = { 0, 1, 4, 4, 1, 5 };

		for (uint32 ty = 0; ty < 3; ++ty)
		{
			for (uint32 tx = 0; tx < 3; ++tx)
			{
				for (uint32 k = 0; k < 6; ++k)
				{
					sprite.indices[(ty * 3 + tx) * 6 + k] = (ty * 4) + tx + rectIndexTable[k];
				}
			}
		}

		sprite.draw(Siv3DEngine::GetRenderer2D()->getBoxShadowTexture());

		return *this;
	}

	template <class SizeType>
	TexturedQuad Rectangle<SizeType>::operator ()(const Texture& texture) const
	{
		return TexturedQuad(texture,
			0.0f, 0.0f, 1.0f, 1.0f,
			{ pos,{ x + w, y },{ x + w, y + h },{ x, y + h } },
			center());
	}

	template <class SizeType>
	TexturedQuad Rectangle<SizeType>::operator ()(const TextureRegion& textureRegion) const
	{
		return TexturedQuad(textureRegion.texture,
			textureRegion.uvRect,
			{ pos,{ x + w, y },{ x + w, y + h },{ x, y + h } },
			center());
	}

	void Formatter(FormatData& formatData, const Rect& value)
	{
		const size_t bufferSize = 12 * 4 + 6;
		wchar buf[bufferSize];
		wchar* p = buf;

		*(p++) = L'(';
		detail::AppendInt(&p, value.x);
		*(p++) = L',';
		detail::AppendInt(&p, value.y);
		*(p++) = L',';
		detail::AppendInt(&p, value.w);
		*(p++) = L',';
		detail::AppendInt(&p, value.h);
		*(p++) = L')';

		formatData.string.append(buf, p - buf);
	}

	void Formatter(FormatData& formatData, const RectF& value)
	{
		Formatter(formatData, Vec4(value.x, value.y, value.w, value.h));
	}

	template struct Rectangle<Point>;
	
	template struct Rectangle<Vec2>;
}
