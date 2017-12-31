//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/TextBox.hpp>
# include "CTextBox.hpp"

namespace s3d
{
	TextBox::TextBox()
		: pImpl(std::make_shared<CTextBox>())
	{

	}

	TextBox::TextBox(const Font& font,
		const Vec2& pos,
		double boxWidth,
		const Optional<size_t>& maxChars,
		const String& defaultText)
		: pImpl(std::make_shared<CTextBox>(font, RectF(pos, boxWidth, font.height() + 2), maxChars, defaultText))
	{

	}

	TextBox::TextBox(const Font& font,
		const Arg::center_<Vec2> center,
		double boxWidth,
		const Optional<size_t>& maxChars,
		const String& defaultText)
		: pImpl(std::make_shared<CTextBox>(font, RectF(center, boxWidth, font.height() + 2), maxChars, defaultText))
	{

	}

	TextBox::~TextBox()
	{

	}

	TextBox::State TextBox::update(const bool clicked)
	{
		return pImpl->update(clicked);
	}

	void TextBox::draw(const Style& style) const
	{
		pImpl->draw(style);
	}

	void TextBox::drawOverlay(const Style& style) const
	{
		pImpl->drawOverlay(style);
	}

	void TextBox::setActive(const bool active)
	{
		pImpl->setActive(active);
	}

	bool TextBox::isActive() const
	{
		return pImpl->isActive();
	}

	const RectF& TextBox::getRect() const
	{
		return pImpl->getRect();
	}

	void TextBox::setPos(const Vec2& pos)
	{
		pImpl->setPos(pos);
	}

	void TextBox::setCenter(const Vec2& center)
	{
		pImpl->setCenter(center);
	}

	void TextBox::setText(const String& text)
	{
		pImpl->setText(text);
	}

	const String& TextBox::getText() const
	{
		return pImpl->getText();
	}
}
