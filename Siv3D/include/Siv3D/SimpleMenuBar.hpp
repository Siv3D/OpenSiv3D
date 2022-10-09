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

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "Optional.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	struct MenuBarItemIndex
	{
		size_t menuIndex = 0;

		size_t itemIndex = 0;

		friend constexpr bool operator ==(const MenuBarItemIndex& lhs, const MenuBarItemIndex& rhs) noexcept
		{
			return ((lhs.menuIndex == rhs.menuIndex) && (lhs.itemIndex == rhs.itemIndex));
		}

		friend constexpr bool operator !=(const MenuBarItemIndex& lhs, const MenuBarItemIndex& rhs) noexcept
		{
			return ((lhs.menuIndex != rhs.menuIndex) || (lhs.itemIndex != rhs.itemIndex));
		}
	};

	class SimpleMenuBar
	{
	public:

		static constexpr int32 MenuBarHeight = 30;

		struct ColorPalette
		{
			ColorF menuBarColor{ 0.88 };

			ColorF activeMenuColor{ 0.8 };

			ColorF menuTextColor{ 0.11 };

			ColorF itemBoxColor{ 0.99 };

			ColorF itemRectColor{ 0.88 };

			ColorF itemTextColor{ 0.11 };

			ColorF itemMouseoverTextColor{ 0.11 };

			ColorF itemDisabledTextColor{ 0.8 };

			ColorF itemRectShadowColor{ 0.0, 0.5 };
		};

		SimpleMenuBar() = default;

		explicit SimpleMenuBar(const Array<std::pair<String, Array<String>>>& menus);

		Optional<MenuBarItemIndex> update();

		void draw() const;

		SimpleMenuBar& setItemEnabled(size_t menuIndex, size_t itemIndex, bool enbaled);

		SimpleMenuBar& setItemEnabled(const MenuBarItemIndex& itemIndex, bool enbaled);

		bool getItemEnabled(size_t menuIndex, size_t itemIndex) const;

		bool getItemEnabled(const MenuBarItemIndex& itemIndex) const;

		void setColorPalette(const ColorPalette& palette) noexcept;

	private:

		static constexpr int32 MenuPadding = 14;

		static constexpr int32 FontSize = 16;

		static constexpr int32 ItemPaddingLeft = 24;

		static constexpr int32 ItemPaddingRight = (ItemPaddingLeft + 4);

		static constexpr int32 ItemPaddingY = 5;

		static constexpr int32 ItemHeight = 34;

		struct Menu
		{
			String name;

			Rect menuRect;

			Rect itemBoxRect;

			Array<String> items;

			Array<bool> itemsEnabled;
		};

		Array<Menu> m_menus;

		Optional<size_t> m_mouseOverMenu;

		Optional<size_t> m_openMenu;

		Optional<size_t> m_mouseOverItem;

		Rect m_rect = Rect::Empty();

		ColorPalette m_palette;

		void reset() noexcept;
	};
}