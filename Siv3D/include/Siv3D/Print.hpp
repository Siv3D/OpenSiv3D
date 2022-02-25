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
# include "Font.hpp"
# include "Formatter.hpp"

namespace s3d
{
	namespace detail
	{
		struct PrintBuffer
		{
			std::unique_ptr<FormatData> formatData;

			PrintBuffer();

			PrintBuffer(PrintBuffer&& other) noexcept;

			~PrintBuffer();

			SIV3D_CONCEPT_FORMATTABLE
			PrintBuffer& operator <<(const Formattable& value)
			{
				Formatter(*formatData, value);

				return *this;
			}
		};

		struct Print_impl
		{
			void write(const char32_t* s) const;

			void write(StringView s) const;

			void write(const String& s) const;

			void writeln(const char32_t* s) const;

			void writeln(StringView s) const;

			void writeln(const String& s) const;

			void operator ()(const char32_t* s) const;

			void operator ()(StringView s) const;

			void operator ()(const String& s) const;

		# if __cpp_lib_concepts

			template <Concept::Formattable... Args>
			void write(const Args&... args) const
			{
				return write(Format(args...));
			}

			// Format できない値が Print.write() に渡されたときに発生するエラーです
			template <class... Args>
			void write(const Args&... args) const = delete;

			template <Concept::Formattable... Args>
			void writeln(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			// Format できない値が Print.writeln() に渡されたときに発生するエラーです
			template <class... Args>
			void writeln(const Args&... args) const = delete;

			template <Concept::Formattable... Args>
			void operator ()(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			// Format できない値が Print() に渡されたときに発生するエラーです
			template <class... Args>
			void operator ()(const Args&... args) const = delete;

		# else

			template <class... Args>
			void write(const Args&... args) const
			{
				return write(Format(args...));
			}

			template <class... Args>
			void writeln(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

			template <class... Args>
			void operator ()(const Args&... args) const
			{
				return write(Format(args..., U'\n'));
			}

		# endif

			/// @brief Format 可能な値を Print で出力するバッファに追加します。
			/// @tparam Formattable 値の型（Format 可能な型でないといけません）
			/// @param value 出力する値
			/// @return Print 出力のバッファ
			SIV3D_CONCEPT_FORMATTABLE
			PrintBuffer operator <<(const Formattable& value) const
			{
				PrintBuffer buf;

				Formatter(*buf.formatData, value);

				return buf;
			}

			/// @brief `Print` で使われるフォントを変更します。
			/// @param font 新しいフォント
			/// @return フォントの変更に成功した場合 true, それ以外の場合は false
			bool setFont(const Font& font) const;

			/// @brief `Print` で使われているフォントを返します。
			/// @return `Print` で使われているフォント
			[[nodiscard]]
			const Font& getFont() const;
		};
	}

	/// @brief 画面にテキストをデバッグ出力するオブジェクトです。`<<` で値を送ります。
	inline constexpr auto Print = detail::Print_impl{};

	/// @brief `Print` でデバッグ出力した内容をクリアします。
	void ClearPrint();
}
