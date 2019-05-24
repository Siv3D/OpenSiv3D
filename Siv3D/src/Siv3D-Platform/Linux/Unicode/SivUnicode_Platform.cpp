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

# include <Siv3D/String.hpp>
# include <Siv3D/StringView.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	namespace Unicode
	{
		String Widen(const std::string_view view)
		{
			return FromUTF8(view);
		}

		std::string Narrow(const StringView view)
		{
			return ToUTF8(view);
		}

		std::wstring ToWString(const StringView view)
		{
			return std::wstring(view.begin(), view.end());
		}

		String FromWString(const std::wstring_view view)
		{
			return String(view.begin(), view.end());
		}
	}
}
