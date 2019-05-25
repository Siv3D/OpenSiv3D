//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <miniutf/miniutf.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/StringView.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Windows.hpp>

namespace s3d::detail
{
	[[nodiscard]] size_t UTF16Length(const StringView view) noexcept;
	void UTF16Encode(char16** s, const char32_t codePoint) noexcept;

	[[nodiscard]] static size_t UTF32Length(const std::wstring_view view)
	{
		size_t length = 0;

		const char16* pSrc = static_cast<const char16*>(static_cast<const void*>(view.data()));
		const char16* const pSrcEnd = pSrc + view.size();

		while (pSrc != pSrcEnd)
		{
			int32 offset;

			utf16_decode(pSrc, pSrcEnd - pSrc, offset);

			pSrc += offset;

			++length;
		}

		return length;
	}

	[[nodiscard]] static std::string FromString(const std::u16string_view view, const uint32 code)
	{
		if (view.empty())
		{
			return std::string();
		}

		const int32 length = ::WideCharToMultiByte(code, 0,
			static_cast<const wchar_t*>(static_cast<const void*>(view.data())),
			static_cast<int>(view.length()), nullptr, 0, nullptr, nullptr);

		std::string result(length, '\0');

		if (length != ::WideCharToMultiByte(code, 0,
			static_cast<const wchar_t*>(static_cast<const void*>(view.data())),
			static_cast<int>(view.length()), &result[0], length, nullptr, nullptr))
		{
			result.clear();
		}

		return result;
	}

	[[nodiscard]] static std::u16string ToString(const std::string_view view, const uint32 code)
	{
		if (view.empty())
		{
			return std::u16string();
		}

		const int32 length = ::MultiByteToWideChar(code, 0, view.data(), static_cast<int32>(view.length()),
			nullptr, 0);

		if (length == 0)
		{
			return std::u16string();
		}

		std::u16string result(length, u'\0');

		if (length != ::MultiByteToWideChar(code, 0, view.data(), static_cast<int32>(view.length()),		
			static_cast<wchar_t*>(static_cast<void*>(&result[0])), length))
		{
			result.clear();
		}

		return result;
	}
}

namespace s3d
{
	namespace Unicode
	{
		String Widen(const std::string_view view)
		{
			return FromUTF16(detail::ToString(view, CP_ACP));
		}

		std::string Narrow(const StringView view)
		{
			return detail::FromString(ToUTF16(view), CP_THREAD_ACP);
		}

		std::wstring ToWString(const StringView view)
		{
			std::wstring result(detail::UTF16Length(view), u'0');

			const char32* pSrc = view.data();
			const char32* const pSrcEnd = pSrc + view.size();
			char16* pDst = static_cast<char16*>(static_cast<void*>(&result[0]));

			while (pSrc != pSrcEnd)
			{
				detail::UTF16Encode(&pDst, *pSrc++);
			}

			return result;
		}

		String FromWString(const std::wstring_view view)
		{
			String result(detail::UTF32Length(view), '0');

			const char16* pSrc = static_cast<const char16*>(static_cast<const void*>(view.data()));
			const char16* const pSrcEnd = pSrc + view.size();
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;

				*pDst++ = detail::utf16_decode(pSrc, pSrcEnd - pSrc, offset);

				pSrc += offset;
			}

			return result;
		}
	}
}
