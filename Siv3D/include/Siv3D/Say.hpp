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
# include <memory>
# include "Common.hpp"
# include "Formatter.hpp"

namespace s3d
{
	namespace detail
	{
		struct SayBuffer
		{
			std::unique_ptr<FormatData> formatData;

			SayBuffer();

			SayBuffer(SayBuffer&& other) noexcept;

			~SayBuffer();

			SIV3D_CONCEPT_FORMATTABLE
			SayBuffer& operator <<(const Formattable& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};

		struct Say_impl
		{
			void operator ()(const char32_t* s) const;

			void operator ()(StringView s) const;

			void operator ()(const String& s) const;

		# if __cpp_lib_concepts

			template <Concept::Formattable... Args>
			void operator ()(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			// Format できない値が Say() に渡されたときに発生するエラーです
			template <class... Args>
			void operator ()(const Args&... args) const = delete;

		# else

			template <class... Args>
			void operator ()(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

		# endif

			/// @brief Format 可能な値を Say で出力するバッファに追加します。
			/// @tparam Formattable 値の型（Format 可能な型でないといけません）
			/// @param value 出力する値
			/// @return Say 出力のバッファ
			SIV3D_CONCEPT_FORMATTABLE
			SayBuffer operator <<(const Formattable& value) const
			{
				SayBuffer buf;

				Formatter(*buf.formatData, value);

				return buf;
			}
		};
	}

	/// @brief テキスト読み上げを行うオブジェクトです。`<<` で値を送ります。
	inline constexpr auto Say = detail::Say_impl{};
}
