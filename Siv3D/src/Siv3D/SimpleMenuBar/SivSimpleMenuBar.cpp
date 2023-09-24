//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
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
# include <Siv3D/Cursor.hpp>
# include <Siv3D/CursorStyle.hpp>

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

			Array<Menu::Item> items(menu.second.size());

			for (size_t i = 0; i < items.size(); ++i)
			{
				String label = menu.second[i];

				if (label && InRange<char32>(label.front(), 0xF0000, 0x10FFFF))
				{
					items[i].icon = label.front();
					label.pop_front();
				}

				items[i].label = std::move(label);
			}

			m_menus.push_back({ menu.first, menuRect, itemBoxRect, std::move(items) });

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
						if (menu.items[*m_mouseOverItem].enabled)
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

		if (m_rect.mouseOver() || m_openMenu)
		{
			Cursor::RequestStyle(CursorStyle::Default);
		}

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

			if (m_mouseOverItem && menu.items[*m_mouseOverItem].enabled)
			{
				const Rect itemRect{ itemBoxRect.x, (itemBoxRect.y + ItemPaddingY + (*m_mouseOverItem * ItemHeight)), itemBoxRect.w, ItemHeight };

				itemRect.stretched(-4, -2).rounded(3.5).draw(m_palette.itemMouseoverColor);
			}

			Point pos{ itemBoxRect.pos.movedBy(ItemPaddingLeft, ItemPaddingY) };

			for (auto&& [i, item] : Indexed(menu.items))
			{
				const ColorF textColor = (item.enabled ? ((i == m_mouseOverItem) ? m_palette.itemMouseoverTextColor : m_palette.itemTextColor)
					: m_palette.itemDisabledTextColor);

				if (item.checked)
				{
					font(U"\U000F012C").draw((FontSize * 1.25), Arg::leftCenter((pos.x - ItemPaddingLeft * 0.75), pos.y + (ItemHeight / 2)),
						textColor);
				}
				else if (item.icon)
				{
					font(item.icon).draw((FontSize * 1.25), Arg::leftCenter((pos.x - ItemPaddingLeft * 0.75), pos.y + (ItemHeight / 2)),
						textColor);
				}

				font(item.label).draw(FontSize, Arg::leftCenter(pos.x, pos.y + (ItemHeight / 2)),
					textColor);

				pos.y += ItemHeight;
			}
		}
	}

	SimpleMenuBar& SimpleMenuBar::setItemEnabled(const size_t menuIndex, const size_t itemIndex, const bool enabled)
	{
		return setItemEnabled(MenuBarItemIndex{ menuIndex, itemIndex }, enabled);
	}

	SimpleMenuBar& SimpleMenuBar::setItemEnabled(const MenuBarItemIndex& itemIndex, const bool enabled)
	{
		assert(itemIndex.menuIndex < m_menus.size());
		assert(itemIndex.itemIndex < m_menus[itemIndex.menuIndex].items.size());
		m_menus[itemIndex.menuIndex].items[itemIndex.itemIndex].enabled = enabled;
		return *this;
	}

	bool SimpleMenuBar::getItemEnabled(const size_t menuIndex, const size_t itemIndex) const
	{
		return getItemEnabled(MenuBarItemIndex{ menuIndex, itemIndex });
	}

	bool SimpleMenuBar::getItemEnabled(const MenuBarItemIndex& itemIndex) const
	{
		assert(itemIndex.menuIndex < m_menus.size());
		assert(itemIndex.itemIndex < m_menus[itemIndex.menuIndex].items.size());
		return m_menus[itemIndex.menuIndex].items[itemIndex.itemIndex].enabled;
	}

	SimpleMenuBar& SimpleMenuBar::setItemChecked(const size_t menuIndex, const size_t itemIndex, const bool checked)
	{
		return setItemChecked(MenuBarItemIndex{ menuIndex, itemIndex }, checked);
	}

	SimpleMenuBar& SimpleMenuBar::setItemChecked(const MenuBarItemIndex& itemIndex, const bool checked)
	{
		assert(itemIndex.menuIndex < m_menus.size());
		assert(itemIndex.itemIndex < m_menus[itemIndex.menuIndex].items.size());
		m_menus[itemIndex.menuIndex].items[itemIndex.itemIndex].checked = checked;
		return *this;
	}

	bool SimpleMenuBar::getItemChecked(const size_t menuIndex, const size_t itemIndex) const
	{
		return getItemChecked(MenuBarItemIndex{ menuIndex, itemIndex });
	}

	bool SimpleMenuBar::getItemChecked(const MenuBarItemIndex& itemIndex) const
	{
		assert(itemIndex.menuIndex < m_menus.size());
		assert(itemIndex.itemIndex < m_menus[itemIndex.menuIndex].items.size());
		return m_menus[itemIndex.menuIndex].items[itemIndex.itemIndex].checked;
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
