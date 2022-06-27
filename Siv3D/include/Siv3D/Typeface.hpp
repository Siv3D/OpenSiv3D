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

namespace s3d
{
	enum class Typeface : uint8
	{
		/// @brief 日本向けの　CJK フォント
		CJK_Regular_JP,

		/// @brief 韓国向けの CJK フォント
		CJK_Regular_KR,

		/// @brief 中国向けの CJK フォント
		CJK_Regular_SC,

		/// @brief 台湾向けの CJK フォント
		CJK_Regular_TC,

		/// @brief 香港向けの CJK フォント
		CJK_Regular_HK,

		/// @brief モノクロ絵文字フォント
		MonochromeEmoji,

		/// @brief カラー絵文字フォント
		ColorEmoji,

		/// @brief 細いサイズの M+ フォント
		Mplus_Thin,

		/// @brief やや細いサイズの M+ フォント	
		Mplus_Light,

		/// @brief 通常サイズの M+ フォント	
		Mplus_Regular,

		/// @brief やや太いサイズの M+ フォント	
		Mplus_Medium,

		/// @brief 太いサイズの M+ フォント
		Mplus_Bold,

		/// @brief とても太いサイズの M+ フォント
		Mplus_Heavy,

		/// @brief 最も太いサイズの M+ フォント	
		Mplus_Black,

		/// @brief Font Awesome Solid アイコンフォント
		Icon_Awesome_Solid,
		
		/// @brief Font Awesome Brand アイコンフォント
		Icon_Awesome_Brand,
		
		/// @brief マテリアルデザイン・アイコンフォント
		Icon_MaterialDesign,

		/// @brief 細いサイズの M+ フォント
		Thin = Mplus_Thin,

		/// @brief やや細いサイズの M+ フォント
		Light = Mplus_Light,

		/// @brief 通常サイズの M+ フォント
		Regular = Mplus_Regular,

		/// @brief やや太いサイズの M+ フォント
		Medium = Mplus_Medium,

		/// @brief 太いサイズの M+ フォント
		Bold = Mplus_Bold,

		/// @brief とても太いサイズの M+ フォント
		Heavy = Mplus_Heavy,

		/// @brief 最も太いサイズの M+ フォント
		Black = Mplus_Black,
	};
}
