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

# include <Siv3D/Font.hpp>
# include <Siv3D/PolygonGlyph.hpp>
# include <Siv3D/MeshGlyph.hpp>
# include <Siv3D/OutlineGlyph.hpp>
# include <Siv3D/BitmapGlyph.hpp>
# include <Siv3D/SDFGlyph.hpp>
# include <Siv3D/MSDFGlyph.hpp>
# include <Siv3D/DrawableText.hpp>
# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/MeshData.hpp>
# include <Siv3D/EngineLog.hpp>
# include "FontFaceProperty.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static constexpr Float3 FromFloat2(const Float2& pos) noexcept
		{
			return{ pos.x, -pos.y, 0.0f };
		}

		[[nodiscard]]
		static MeshData FromPolygons(const MultiPolygon& polygons)
		{
			Array<Vertex3D> vertices;
			Array<TriangleIndex32> indices;

			Vertex3D v;
			v.normal = Float3{ 0.0f, 0.0f, -1.0f };
			v.tex = Float2{ 0.0f,0.0f };

			uint32 indexOffset = 0;

			for (const auto& polygon : polygons)
			{
				for (const auto& point : polygon.vertices())
				{
					v.pos = FromFloat2(point);
					vertices << v;
				}

				for (const auto& t : polygon.indices())
				{
					indices.push_back(TriangleIndex32{ (indexOffset + t.i0), (indexOffset + t.i1), (indexOffset + t.i2) });
				}

				indexOffset = static_cast<uint32>(vertices.size());
			}

			return{ std::move(vertices), std::move(indices) };
		}

		[[nodiscard]]
		static MeshGlyph ToMeshGlyph(const PolygonGlyph& polygonGlyph, const double size, const Font& font)
		{
			const double scale = (size / font.fontSize());
			const double offsetX = (polygonGlyph.polygons.computeBoundingRect().w + polygonGlyph.getBase().x);
			const MultiPolygon polygons = polygonGlyph.polygons.movedBy(polygonGlyph.getBase()).scaled(scale);

			return
			{
				.mesh = Mesh{ FromPolygons(polygons) },
				.glyphIndex = polygonGlyph.glyphIndex,
				.xAdvance = (polygonGlyph.xAdvance * scale),
				.yAdvance = (polygonGlyph.yAdvance * scale),
				.xOffset = (offsetX * 0.5 * scale),
			};
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Font>>::AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`Font` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Font>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Font))
		{
			p->release(m_id);
		}
	}

	Font::Font() {}

	Font::Font(const int32 fontSize, const FilePathView path, const FontStyle style)
		: Font{ FontMethod::Bitmap, fontSize, path, 0, style } {}

	Font::Font(const int32 fontSize, const FilePathView path, const size_t faceIndex, const FontStyle style)
		: Font{ FontMethod::Bitmap, fontSize, path, faceIndex, style } {}

	Font::Font(const int32 fontSize, const Typeface typeface, const FontStyle style)
		: Font{ FontMethod::Bitmap, fontSize, typeface, style } {}

	Font::Font(const FontMethod fontMethod, const int32 fontSize, const FilePathView path, const FontStyle style)
		: Font{ fontMethod, fontSize, path, 0, style } {}

	Font::Font(const FontMethod fontMethod, const int32 fontSize, const FilePathView path, const size_t faceIndex, const FontStyle style)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Font)->create(path, faceIndex, fontMethod, fontSize, style)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Font::Font(const FontMethod fontMethod, const int32 fontSize, const Typeface typeface, const FontStyle style)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Font)->create(typeface, fontMethod, fontSize, style)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Font::~Font() {}

	bool Font::addFallback(const Font& font) const
	{
		if (not font)
		{
			LOG_FAIL(U"Font::addFallback() failed (font is empty)");
			return false;
		}

		return SIV3D_ENGINE(Font)->addFallbackFont(m_handle->id(), font.m_handle);
	}

	const String& Font::familyName() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).familiyName;
	}

	const String& Font::styleName() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).styleName;
	}

	bool Font::hasColor() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).hasColor;
	}

	FontStyle Font::style() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).style;
	}

	FontMethod Font::method() const
	{
		return SIV3D_ENGINE(Font)->getMethod(m_handle->id());
	}

	int32 Font::fontSize() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).fontPixelSize;
	}

	int32 Font::ascender() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).ascender;
	}

	int32 Font::descender() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).descender;
	}

	int32 Font::height() const
	{
		const auto& prop = SIV3D_ENGINE(Font)->getProperty(m_handle->id());

		return (prop.ascender + prop.descender);
	}

	double Font::height(const double size) const
	{
		const auto& prop = SIV3D_ENGINE(Font)->getProperty(m_handle->id());

		return ((prop.ascender + prop.descender) * (size / prop.fontPixelSize));
	}

	double Font::spaceWidth() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).spaceWidth;
	}

	int32 Font::indentSize() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).indentSize;
	}

	const Font& Font::setIndentSize(const int32 indentSize) const
	{
		SIV3D_ENGINE(Font)->setIndentSize(m_handle->id(), indentSize);

		return *this;
	}

	const Font& Font::setBufferThickness(const int32 thickness) const
	{
		SIV3D_ENGINE(Font)->setBufferThickness(m_handle->id(), thickness);

		return *this;
	}

	int32 Font::getBufferThickness() const
	{
		return SIV3D_ENGINE(Font)->getBufferThickness(m_handle->id());
	}

	bool Font::hasGlyph(const char32 ch) const
	{
		return SIV3D_ENGINE(Font)->hasGlyph(m_handle->id(), StringView(&ch, 1));
	}

	bool Font::hasGlyph(const StringView ch) const
	{
		return SIV3D_ENGINE(Font)->hasGlyph(m_handle->id(), ch);
	}

	uint32 Font::num_glyphs() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).numGlyphs;
	}

	GlyphIndex Font::getGlyphIndex(const char32 ch) const
	{
		return SIV3D_ENGINE(Font)->getGlyphIndex(m_handle->id(), StringView(&ch, 1));
	}

	GlyphIndex Font::getGlyphIndex(const StringView ch) const
	{
		return SIV3D_ENGINE(Font)->getGlyphIndex(m_handle->id(), ch);
	}

	Array<GlyphCluster> Font::getGlyphClusters(const StringView s, const UseFallback useFallback, const Ligature ligature) const
	{
		return SIV3D_ENGINE(Font)->getGlyphClusters(m_handle->id(), s, useFallback.getBool(), ligature);
	}

	GlyphInfo Font::getGlyphInfo(const char32 ch) const
	{
		return SIV3D_ENGINE(Font)->getGlyphInfo(m_handle->id(), StringView(&ch, 1));
	}

	GlyphInfo Font::getGlyphInfo(const StringView ch) const
	{
		return SIV3D_ENGINE(Font)->getGlyphInfo(m_handle->id(), ch);
	}

	GlyphInfo Font::getGlyphInfoByGlyphIndex(const GlyphIndex glyphIndex) const
	{
		return SIV3D_ENGINE(Font)->getGlyphInfoByGlyphIndex(m_handle->id(), glyphIndex);
	}

	OutlineGlyph Font::renderOutline(const char32 ch, const CloseRing closeRing) const
	{
		return SIV3D_ENGINE(Font)->renderOutline(m_handle->id(), StringView(&ch, 1), closeRing);
	}

	OutlineGlyph Font::renderOutline(const StringView ch, const CloseRing closeRing) const
	{
		return SIV3D_ENGINE(Font)->renderOutline(m_handle->id(), ch, closeRing);
	}

	OutlineGlyph Font::renderOutlineByGlyphIndex(const GlyphIndex glyphIndex, const CloseRing closeRing) const
	{
		return SIV3D_ENGINE(Font)->renderOutlineByGlyphIndex(m_handle->id(), glyphIndex, closeRing);
	}

	Array<OutlineGlyph> Font::renderOutlines(const StringView s, const CloseRing closeRing, const Ligature ligature) const
	{
		return SIV3D_ENGINE(Font)->renderOutlines(m_handle->id(), s, closeRing, ligature);
	}

	PolygonGlyph Font::renderPolygon(const char32 ch) const
	{
		return SIV3D_ENGINE(Font)->renderPolygon(m_handle->id(), StringView(&ch, 1));
	}

	PolygonGlyph Font::renderPolygon(const StringView ch) const
	{
		return SIV3D_ENGINE(Font)->renderPolygon(m_handle->id(), ch);
	}

	PolygonGlyph Font::renderPolygonByGlyphIndex(const GlyphIndex glyphIndex) const
	{
		return SIV3D_ENGINE(Font)->renderPolygonByGlyphIndex(m_handle->id(), glyphIndex);
	}

	Array<PolygonGlyph> Font::renderPolygons(const StringView s, const Ligature ligature) const
	{
		return SIV3D_ENGINE(Font)->renderPolygons(m_handle->id(), s, ligature);
	}

	MeshGlyph Font::createMesh(const char32 ch, const double size) const
	{
		const PolygonGlyph polygonGlyph = SIV3D_ENGINE(Font)->renderPolygon(m_handle->id(), StringView(&ch, 1));
	
		return detail::ToMeshGlyph(polygonGlyph, size, *this);
	}

	MeshGlyph Font::createMesh(const StringView ch, const double size) const
	{
		const PolygonGlyph polygonGlyph = SIV3D_ENGINE(Font)->renderPolygon(m_handle->id(), ch);

		return detail::ToMeshGlyph(polygonGlyph, size, *this);
	}

	MeshGlyph Font::createMeshByGlyphIndex(const GlyphIndex glyphIndex, const double size) const
	{
		const PolygonGlyph polygonGlyph = SIV3D_ENGINE(Font)->renderPolygonByGlyphIndex(m_handle->id(), glyphIndex);

		return detail::ToMeshGlyph(polygonGlyph, size, *this);
	}

	Array<MeshGlyph> Font::createMeshes(const StringView s, const double size, const Ligature ligature) const
	{
		const Array<PolygonGlyph> polygonGlyphs = SIV3D_ENGINE(Font)->renderPolygons(m_handle->id(), s, ligature);

		return polygonGlyphs.map([size, this](const PolygonGlyph& polygonGlyph) { return detail::ToMeshGlyph(polygonGlyph, size, *this); });
	}

	BitmapGlyph Font::renderBitmap(const char32 ch) const
	{
		return SIV3D_ENGINE(Font)->renderBitmap(m_handle->id(), StringView(&ch, 1));
	}

	BitmapGlyph Font::renderBitmap(const StringView ch) const
	{
		return SIV3D_ENGINE(Font)->renderBitmap(m_handle->id(), ch);
	}

	BitmapGlyph Font::renderBitmapByGlyphIndex(const GlyphIndex glyphIndex) const
	{
		return SIV3D_ENGINE(Font)->renderBitmapByGlyphIndex(m_handle->id(), glyphIndex);
	}

	SDFGlyph Font::renderSDF(const char32 ch, const int32 buffer) const
	{
		return SIV3D_ENGINE(Font)->renderSDF(m_handle->id(), StringView(&ch, 1), buffer);
	}

	SDFGlyph Font::renderSDF(const StringView ch, const int32 buffer) const
	{
		return SIV3D_ENGINE(Font)->renderSDF(m_handle->id(), ch, buffer);
	}

	SDFGlyph Font::renderSDFByGlyphIndex(const GlyphIndex glyphIndex, const int32 buffer) const
	{
		return SIV3D_ENGINE(Font)->renderSDFByGlyphIndex(m_handle->id(), glyphIndex, buffer);
	}

	MSDFGlyph Font::renderMSDF(const char32 ch, const int32 buffer) const
	{
		return SIV3D_ENGINE(Font)->renderMSDF(m_handle->id(), StringView(&ch, 1), buffer);
	}

	MSDFGlyph Font::renderMSDF(const StringView ch, const int32 buffer) const
	{
		return SIV3D_ENGINE(Font)->renderMSDF(m_handle->id(), ch, buffer);
	}

	MSDFGlyph Font::renderMSDFByGlyphIndex(const GlyphIndex glyphIndex, const int32 buffer) const
	{
		return SIV3D_ENGINE(Font)->renderMSDFByGlyphIndex(m_handle->id(), glyphIndex, buffer);
	}

	bool Font::preload(const StringView chars) const
	{
		return SIV3D_ENGINE(Font)->preload(m_handle->id(), chars);
	}

	const Texture& Font::getTexture() const
	{
		return SIV3D_ENGINE(Font)->getTexture(m_handle->id());
	}

	Glyph Font::getGlyph(const char32 ch) const
	{
		return SIV3D_ENGINE(Font)->getGlyph(m_handle->id(), StringView(&ch, 1));
	}

	Glyph Font::getGlyph(const StringView ch) const
	{
		return SIV3D_ENGINE(Font)->getGlyph(m_handle->id(), ch);
	}

	Array<Glyph> Font::getGlyphs(const StringView s, const Ligature ligature) const
	{
		return SIV3D_ENGINE(Font)->getGlyphs(m_handle->id(), s, ligature);
	}

	DrawableText Font::operator()(const String& text) const
	{
		return{ *this, text };
	}

	DrawableText Font::operator()(String&& text) const
	{
		return{ *this, std::move(text) };
	}

	void Font::swap(Font& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}

	const PixelShader& Font::GetPixelShader(const FontMethod method, const TextStyle::Type type, const HasColor hasColor)
	{
		return SIV3D_ENGINE(Font)->getFontShader(method, type, hasColor);
	}

	bool Font::IsAvailable(const Typeface typeface)
	{
		return SIV3D_ENGINE(Font)->isAvailable(typeface);
	}
}
