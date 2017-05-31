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

# include "../Siv3DEngine.hpp"
# include "IFont.hpp"
# include <Siv3D/Font.hpp>

namespace s3d
{
	template <>
	AssetHandle<Font::Handle>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::GetFont())
		{
			p->release(m_id);
		}
	}

	Font::Font()
		: m_handle(std::make_shared<FontHandle>())
	{

	}

	Font::Font(const int32 fontSize, const FilePath& path, const FontStyle style)
		: m_handle(std::make_shared<FontHandle>(Siv3DEngine::GetFont()->create(path, fontSize, style)))
	{

	}

	Font::~Font()
	{

	}

	void Font::release()
	{
		m_handle = std::make_shared<FontHandle>();
	}

	bool Font::isEmpty() const
	{
		return m_handle->getID() == FontHandle::NullID;
	}

	Font::IDType Font::id() const
	{
		return m_handle->getID();
	}

	bool Font::operator ==(const Font& shader) const
	{
		return m_handle->getID() == shader.m_handle->getID();
	}

	bool Font::operator !=(const Font& shader) const
	{
		return m_handle->getID() != shader.m_handle->getID();
	}

	int32 Font::ascender() const
	{
		return Siv3DEngine::GetFont()->getAscender(m_handle->getID());
	}

	int32 Font::descender() const
	{
		return Siv3DEngine::GetFont()->getDescender(m_handle->getID());
	}

	RectF DrawableText::boundingRect(const Vec2& pos) const
	{
		return Siv3DEngine::GetFont()->getBoundingRect(font.id(), text, 1.0).moveBy(pos);
	}

	RectF DrawableText::region(const Vec2& pos) const
	{
		return Siv3DEngine::GetFont()->getRegion(font.id(), text, 1.0).moveBy(pos);
	}

	RectF DrawableText::draw(const Vec2& pos, const ColorF& color) const
	{
		return Siv3DEngine::GetFont()->draw(font.id(), text, pos, color, 1.0);
	}
}
