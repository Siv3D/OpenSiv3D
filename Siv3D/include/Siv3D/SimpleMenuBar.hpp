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

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "Optional.hpp"
# include "2DShapes.hpp"

namespace s3d
{
	/// @brief メニューバー上のアイテムのインデックス
	struct MenuBarItemIndex
	{
		/// @brief メニューのインデックス
		size_t menuIndex = 0;

		/// @brief アイテムのインデックス
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

	/// @brief メニューバー
	class SimpleMenuBar
	{
	public:

		/// @brief メニューバーの高さ（ピクセル）
		static constexpr int32 MenuBarHeight = 30;

		/// @brief カラーパレット
		struct ColorPalette
		{
			/// @brief メニューバーの背景色
			ColorF menuBarColor{ 0.88 };

			/// @brief アクティブなメニューの背景色
			ColorF activeMenuColor{ 0.8 };

			/// @brief メニューのテキストの色
			ColorF menuTextColor{ 0.11 };

			/// @brief メニューアイテムの背景色
			ColorF itemBoxColor{ 0.99 };

			/// @brief マウスオーバーされているメニューアイテムの背景色
			ColorF itemMouseoverColor{ 0.88 };

			/// @brief メニューアイテムのテキストの色
			ColorF itemTextColor{ 0.11 };

			/// @brief マウスオーバーされているメニューアイテムのテキストの色
			ColorF itemMouseoverTextColor{ 0.11 };

			/// @brief 無効化されているメニューアイテムのテキストの色
			ColorF itemDisabledTextColor{ 0.8 };

			/// @brief メニューアイテムの影の色
			ColorF itemRectShadowColor{ 0.0, 0.5 };
		};

		SimpleMenuBar() = default;

		/// @brief メニューバーを構築します。
		/// @param menus メニューアイテム
		explicit SimpleMenuBar(const Array<std::pair<String, Array<String>>>& menus);

		/// @brief メニューバーを更新します。
		/// @return メニューアイテムが選択された場合、そのアイテムのインデックス。それ以外の場合は none
		Optional<MenuBarItemIndex> update();

		/// @brief メニューバーを描画します。
		void draw() const;

		/// @brief アイテムの有効無効を切り替えます。
		/// @param menuIndex メニューインデックス
		/// @param itemIndex アイテムインデックス
		/// @param enabled 有効にする場合 true, 無効にする場合 false
		/// @return *this
		SimpleMenuBar& setItemEnabled(size_t menuIndex, size_t itemIndex, bool enabled);

		/// @brief アイテムの有効無効を切り替えます。
		/// @param itemIndex アイテムのインデックス
		/// @param enabled 有効にする場合 true, 無効にする場合 false
		/// @return *this
		SimpleMenuBar& setItemEnabled(const MenuBarItemIndex& itemIndex, bool enabled);

		/// @brief アイテムの有効無効を取得します。
		/// @param menuIndex メニューインデックス
		/// @param itemIndex アイテムインデックス
		/// @return 有効である場合 true, 無効である場合 false
		bool getItemEnabled(size_t menuIndex, size_t itemIndex) const;

		/// @brief アイテムの有効無効を取得します。
		/// @param itemIndex アイテムのインデックス
		/// @return 有効である場合 true, 無効である場合 false
		bool getItemEnabled(const MenuBarItemIndex& itemIndex) const;

		/// @brief アイテムがチェックされているかを切り替えます。
		/// @param menuIndex メニューインデックス
		/// @param itemIndex アイテムインデックス
		/// @param checked チェックされている状態にする場合 true, チェックされていない状態にする場合は false
		/// @return *this
		SimpleMenuBar& setItemChecked(size_t menuIndex, size_t itemIndex, bool checked);

		/// @brief アイテムがチェックされているかを切り替えます。
		/// @param itemIndex アイテムのインデックス
		/// @param checked チェックされている状態にする場合 true, チェックされていない状態にする場合は false
		/// @return *this
		SimpleMenuBar& setItemChecked(const MenuBarItemIndex& itemIndex, bool checked);

		/// @brief アイテムがチェックされているかを返します。
		/// @param menuIndex メニューインデックス
		/// @param itemIndex アイテムインデックス
		/// @return チェックされている場合 true, それ以外の場合は false
		bool getItemChecked(size_t menuIndex, size_t itemIndex) const;

		/// @brief アイテムがチェックされているかを返します。
		/// @param itemIndex アイテムのインデックス
		/// @return チェックされている場合 true, それ以外の場合は false
		bool getItemChecked(const MenuBarItemIndex& itemIndex) const;

		/// @brief カラーパレットを変更します。
		/// @param palette 新しいカラーパレット
		/// @return *this
		SimpleMenuBar& setColorPalette(const ColorPalette& palette) noexcept;

	private:

		static constexpr int32 MenuPadding = 14;

		static constexpr int32 FontSize = 16;

		static constexpr int32 ItemPaddingLeft = 40;

		static constexpr int32 ItemPaddingRight = 40;

		static constexpr int32 ItemPaddingY = 5;

		static constexpr int32 ItemHeight = 34;

		struct Menu
		{
			String name;

			Rect menuRect;

			Rect itemBoxRect;

			struct Item
			{
				String label;

				char32 icon = 0;

				bool checked = false;

				bool enabled = true;
			};

			Array<Item> items;
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