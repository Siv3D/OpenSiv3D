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

# include <Siv3D/SimpleMenuBar.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/SimpleGUI.hpp>
# include <Siv3D/Utility.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Font.hpp>
# include <Siv3D/DrawableText.hpp>
# include <Siv3D/Mouse.hpp>
# include <Siv3D/Indexed.hpp>

namespace s3d
{
	SimpleMenuBar::SimpleMenuBar(const Array<std::pair<String, Array<String>>>& menus)
	{
		m_rect = Rect{ 0, 0, Scene::Width(), MenuBarHeight };

		const Font& font = SimpleGUI::GetFont();

		int32 penPosX = 2;

		for (const auto& menu : menus)
		{
			const int32 width = static_cast<int32>(Math::Ceil(font(menu.first).region(FontSize).w));
			const Rect menuRect{ penPosX, 0, (MenuPadding + width + MenuPadding), MenuBarHeight };

			double itemBoxWidth = 0;
			{
				for (const auto& item : menu.second)
				{
					itemBoxWidth = Max(itemBoxWidth, font(item).region(FontSize).w);
				}
			}

			const Rect itemBoxRect{ penPosX,
				(MenuBarHeight - 3),
				(ItemPaddingLeft + static_cast<int32>(Math::Ceil(itemBoxWidth)) + ItemPaddingRight),
				(ItemPaddingY + static_cast<int32>(menu.second.size() * ItemHeight) + ItemPaddingY) };

			m_menus.push_back({ menu.first, menuRect, itemBoxRect, menu.second, Array<bool>(menu.second.size(), true) });

			penPosX += menuRect.w;
		}
	}

	Optional<MenuBarItemIndex> SimpleMenuBar::update()
	{
		Optional<MenuBarItemIndex> result;

		bool handled = false;

		m_rect.w = Scene::Width();

		if (not m_openMenu)
		{
			m_mouseOverMenu.reset();
		}

		m_mouseOverItem.reset();

		if (m_rect.mouseOver())
		{
			for (auto&& [i, menu] : Indexed(m_menus))
			{
				if (menu.menuRect.mouseOver())
				{
					m_mouseOverMenu = i;

					if (MouseL.down())
					{
						if (m_openMenu)
						{
							m_openMenu.reset();
						}
						else
						{
							m_openMenu = i;
						}

						handled = true;
					}
					else if (m_openMenu)
					{
						m_openMenu = i;
					}

					break;
				}
			}

			Mouse::ClearLRInput();
		}

		if (m_openMenu)
		{
			const auto& menu = m_menus[*m_openMenu];

			const Rect& itemBoxRect = menu.itemBoxRect;

			for (auto&& [i, item] : Indexed(menu.items))
			{
				const Rect itemRect{ itemBoxRect.x, (itemBoxRect.y + ItemPaddingY + (i * ItemHeight)), itemBoxRect.w, ItemHeight };

				if (itemRect.mouseOver())
				{
					m_mouseOverItem = i;

					if (MouseL.down())
					{
						if (menu.itemsEnabled[*m_mouseOverItem])
						{
							result = { *m_openMenu, i };

							reset();
						}

						break;
					}
				}
			}

			if (itemBoxRect.mouseOver())
			{
				Mouse::ClearLRInput();
			}
		}

		if (not handled && MouseL.down())
		{
			reset();
		}

		return result;
	}

	void SimpleMenuBar::draw() const
	{
		m_rect.draw(m_palette.menuBarColor);

		if (m_mouseOverMenu)
		{
			m_menus[*m_mouseOverMenu].menuRect.stretched(0, -2).rounded(3.5).draw(m_palette.activeMenuColor);
		}

		const Font& font = SimpleGUI::GetFont();

		for (const auto& menu : m_menus)
		{
			font(menu.name).draw(FontSize, Vec2{ (menu.menuRect.x + MenuPadding), 2 }, m_palette.menuTextColor);
		}

		if (m_openMenu)
		{
			const auto& menu = m_menus[*m_openMenu];

			const Rect& itemBoxRect = menu.itemBoxRect;

			if (m_palette.itemRectShadowColor.a)
			{
				itemBoxRect.rounded(5).drawShadow(Vec2{ 0, 1 }, 9, -1, m_palette.itemRectShadowColor);
			}
		
			itemBoxRect.rounded(5).draw(m_palette.itemBoxColor);

			if (m_mouseOverItem && menu.itemsEnabled[*m_mouseOverItem])
			{
				const Rect itemRect{ itemBoxRect.x, (itemBoxRect.y + ItemPaddingY + (*m_mouseOverItem * ItemHeight)), itemBoxRect.w, ItemHeight };

				itemRect.stretched(-4, -2).rounded(3.5).draw(m_palette.itemMouseoverColor);
			}

			Point pos{ itemBoxRect.pos.movedBy(ItemPaddingLeft, ItemPaddingY) };

			for (auto&& [i, item] : Indexed(menu.items))
			{
				const ColorF textColor = (menu.itemsEnabled[i] ? ((i == m_mouseOverItem) ? m_palette.itemMouseoverTextColor : m_palette.itemTextColor)
					: m_palette.itemDisabledTextColor);

				font(item).draw(FontSize, Arg::leftCenter(pos.x, pos.y + (ItemHeight / 2)),
					textColor);

				pos.y += ItemHeight;
			}
		}
	}

	SimpleMenuBar& SimpleMenuBar::setItemEnabled(const size_t menuIndex, const size_t itemIndex, bool enbaled)
	{
		return setItemEnabled(MenuBarItemIndex{ menuIndex, itemIndex }, enbaled);
	}

	SimpleMenuBar& SimpleMenuBar::setItemEnabled(const MenuBarItemIndex& itemIndex, bool enbaled)
	{
		assert(itemIndex.menuIndex < m_menus.size());
		assert(itemIndex.itemIndex < m_menus[itemIndex.menuIndex].itemsEnabled.size());
		m_menus[itemIndex.menuIndex].itemsEnabled[itemIndex.itemIndex] = enbaled;
		return *this;
	}

	bool SimpleMenuBar::getItemEnabled(const size_t menuIndex, const size_t itemIndex) const
	{
		return getItemEnabled(MenuBarItemIndex{ menuIndex, itemIndex });
	}

	bool SimpleMenuBar::getItemEnabled(const MenuBarItemIndex& itemIndex) const
	{
		assert(itemIndex.menuIndex < m_menus.size());
		assert(itemIndex.itemIndex < m_menus[itemIndex.menuIndex].itemsEnabled.size());
		return m_menus[itemIndex.menuIndex].itemsEnabled[itemIndex.itemIndex];
	}

	SimpleMenuBar& SimpleMenuBar::setColorPalette(const ColorPalette& palette) noexcept
	{
		m_palette = palette;
		return *this;
	}

	void SimpleMenuBar::reset() noexcept
	{
		m_mouseOverMenu.reset();
		m_openMenu.reset();
		m_mouseOverItem.reset();
	}
}
