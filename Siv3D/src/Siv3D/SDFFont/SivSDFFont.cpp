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

# include <Siv3DEngine.hpp>
# include <Siv3D/SDFFont.hpp>
# include <Siv3D/EngineMessageBox.hpp>
# include <AssetHandleManager/AssetReport.hpp>
# include "ISDFFont.hpp"

namespace s3d
{
	template <>
	AssetHandle<SDFFont::Tag>::AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`SDFFont` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<SDFFont::Tag>::AssetHandle(const IDWrapperType id) noexcept
		: m_id(id)
	{
		if (!Siv3DEngine::isActive())
		{
			EngineMessageBox::Show(U"`SDFFont` must be initialized after engine setup.");
			std::exit(-1);
		}
	}

	template <>
	AssetHandle<SDFFont::Tag>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::Get<ISiv3DSDFFont>())
		{
			p->release(m_id);
		}
	}

	SDFFont::SDFFont()
		: m_handle(std::make_shared<SDFFontHandle>())
	{

	}

	SDFFont::SDFFont(const int32 baseSize, const Typeface typeface, const FontStyle style)
		: m_handle(std::make_shared<SDFFontHandle>(Siv3DEngine::Get<ISiv3DSDFFont>()->create(typeface, baseSize, style)))
	{
		ReportAssetCreation();
	}

	SDFFont::SDFFont(const int32 baseSize, const FilePath& path, const FontStyle style)
		: m_handle(std::make_shared<SDFFontHandle>(Siv3DEngine::Get<ISiv3DSDFFont>()->create(path, baseSize, style)))
	{
		ReportAssetCreation();
	}

	SDFFont::~SDFFont()
	{

	}

	void SDFFont::release()
	{
		m_handle = std::make_shared<SDFFontHandle>();
	}

	bool SDFFont::isEmpty() const
	{
		return m_handle->id().isNullAsset();
	}

	SDFFont::operator bool() const
	{
		return !isEmpty();
	}

	SDFFontID SDFFont::id() const
	{
		return m_handle->id();
	}

	bool SDFFont::operator ==(const SDFFont& font) const
	{
		return m_handle->id() == font.m_handle->id();
	}

	bool SDFFont::operator !=(const SDFFont& font) const
	{
		return m_handle->id() != font.m_handle->id();
	}

	const String& SDFFont::familyName() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getFamilyName(m_handle->id());
	}

	const String& SDFFont::styleName() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getStyleName(m_handle->id());
	}

	int32 SDFFont::baseSize() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getBaseSize(m_handle->id());
	}

	int32 SDFFont::ascent() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getAscent(m_handle->id());
	}

	int32 SDFFont::descent() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getDescent(m_handle->id());
	}

	int32 SDFFont::height() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getHeight(m_handle->id());
	}

	Glyph SDFFont::getGlyph(const char32 codePoint) const
	{
		return getGlyphs(StringView(&codePoint, 1)).front();
	}

	Array<Glyph> SDFFont::getGlyphs(const StringView text) const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getGlyphs(m_handle->id(), text);
	}

	const Texture& SDFFont::getTexture() const
	{
		return Siv3DEngine::Get<ISiv3DSDFFont>()->getTexture(m_handle->id());
	}
}
