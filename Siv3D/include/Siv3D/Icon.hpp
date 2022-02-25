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
# include "Image.hpp"

namespace s3d
{
	/// @brief アイコン
	struct Icon
	{
		enum class Type : uint8
		{
			Awesome,

			MaterialDesign,
		};

		/// @brief アイコンパッケージの種類
		Type type = Type::Awesome;

		/// @brief アイコンのコードポイント
		uint32 code = 0;

		SIV3D_NODISCARD_CXX20
		Icon() = default;

		SIV3D_NODISCARD_CXX20
		explicit constexpr Icon(uint32 _code) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Icon(Type _type, uint32 _code) noexcept;

		[[nodiscard]]
		static bool HasGlyph(uint32 code);

		[[nodiscard]]
		static bool HasGlyph(Type type, uint32 code);

		[[nodiscard]]
		static Image CreateImage(uint32 code, int32 size);

		[[nodiscard]]
		static Image CreateImage(Type type, uint32 code, int32 size);

		[[nodiscard]]
		static Image CreateSDFImage(uint32 code, int32 size, int32 buffer = 3);

		[[nodiscard]]
		static Image CreateSDFImage(Type type, uint32 code, int32 size, int32 buffer = 3);

		[[nodiscard]]
		static Image CreateMSDFImage(uint32 code, int32 size, int32 buffer = 3);

		[[nodiscard]]
		static Image CreateMSDFImage(Type type, uint32 code, int32 size, int32 buffer = 3);
	};

	inline namespace Literals
	{
		inline namespace IconLiterals
		{
			[[nodiscard]]
			inline constexpr Icon operator ""_icon(unsigned long long codePoint) noexcept;
		}
	}
}

# include "detail/Icon.ipp"
