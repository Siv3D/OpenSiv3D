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

# include <Siv3D/TextBox.hpp>
# include "CTextBox.hpp"

namespace s3d
{
	TextBox::TextBox()
		: pImpl(std::make_shared<CTextBox>())
	{

	}

	TextBox::TextBox(const Font& font, const double x, const double y, const Optional<double>& width, const String& defaultText, const String& description)
		: pImpl(std::make_shared<CTextBox>(font, x, y, width, defaultText, description))
	{

	}

	bool TextBox::update(const bool clicked) const
	{
		return pImpl->update(clicked);
	}

	void TextBox::drawGlow(const double blurRadius, const double spread, const ColorF& color) const
	{
		pImpl->drawGlow(blurRadius, spread, color);
	}

	void TextBox::drawBox(const ColorF& boxColor) const
	{
		pImpl->drawBox(boxColor);
	}

	void TextBox::drawText(const ColorF& textColor, const ColorF& markedTextColor, const ColorF& descriptionColor) const
	{
		pImpl->drawText(textColor, markedTextColor, descriptionColor);
	}

	void TextBox::draw(const ColorF& boxColor, const ColorF& textColor, const double blurRadius, const double spread, const ColorF& glowColor) const
	{
		pImpl->drawGlow(blurRadius, spread, glowColor);

		pImpl->drawBox(boxColor);

		pImpl->drawText(textColor, ColorF(0.33), ColorF(0.67));
	}

	bool TextBox::isActive() const noexcept
	{
		return pImpl->isActive();
	}

	void TextBox::setPos(const Vec2& pos) noexcept
	{
		pImpl->setPos(pos);
	}

	const Vec2& TextBox::getPos() const noexcept
	{
		return pImpl->getPos();
	}

	void TextBox::setWidth(const Optional<double>& width) noexcept
	{
		pImpl->setWidth(width);
	}

	const Optional<double>& TextBox::getWidth() const noexcept
	{
		return pImpl->getWidth();
	}

	RectF TextBox::getRect() const noexcept
	{
		return pImpl->getRect();
	}

	void TextBox::setText(const String& text)
	{
		pImpl->setText(text);
	}

	const String& TextBox::getText() const
	{
		return pImpl->getText();
	}

	void TextBox::setDescription(const String& text)
	{
		pImpl->setDescription(text);
	}

	const String& TextBox::getDescription() const
	{
		return pImpl->getDescription();
	}
}
