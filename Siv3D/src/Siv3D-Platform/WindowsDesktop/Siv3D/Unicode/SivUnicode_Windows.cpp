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

# include <miniutf/miniutf.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Unicode/UnicodeUtility.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static std::string ToMultiByte(const std::wstring_view s, const uint32 codePage)
		{
			if (s.empty())
			{
				return std::string();
			}

			const int32 requiredSize = ::WideCharToMultiByte(codePage, 0,
				s.data(), static_cast<int>(s.length()),
				nullptr, 0, nullptr, nullptr);

			std::string result(requiredSize, '\0');

			::WideCharToMultiByte(codePage, 0,
				s.data(), static_cast<int>(s.length()),
				&result[0], requiredSize, nullptr, nullptr);

			return result;
		}

		[[nodiscard]]
		static std::u16string FromMultiByte(const std::string_view s, const uint32 code)
		{
			if (s.empty())
			{
				return std::u16string();
			}

			const int32 length = ::MultiByteToWideChar(code, 0, s.data(), static_cast<int32>(s.length()),
				nullptr, 0);

			if (length == 0)
			{
				return std::u16string();
			}

			std::u16string result(length, u'\0');

			if (length != ::MultiByteToWideChar(code, 0, s.data(), static_cast<int32>(s.length()),
				static_cast<wchar_t*>(static_cast<void*>(&result[0])), length))
			{
				result.clear();
			}

			return result;
		}
	}

	namespace Unicode
	{
		String Widen(const std::string_view s)
		{
			return FromUTF16(detail::FromMultiByte(s, CP_ACP));
		}

		String FromWstring(const std::wstring_view s)
		{
			const char16* pSrc = static_cast<const char16*>(static_cast<const void*>(s.data()));
			return FromUTF16(std::u16string_view(pSrc, s.size()));
		}

		std::string Narrow(const StringView s)
		{
			return detail::ToMultiByte(ToWstring(s), CP_ACP);
		}

		std::wstring ToWstring(const StringView s)
		{
			std::wstring result(detail::UTF16_Length(s), L'0');

			const char32* pSrc = s.data();
			const char32* const pSrcEnd = pSrc + s.size();
			wchar_t* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				detail::UTF16_Encode(&pDst, *pSrc++);
			}

			return result;
		}
	}
}
