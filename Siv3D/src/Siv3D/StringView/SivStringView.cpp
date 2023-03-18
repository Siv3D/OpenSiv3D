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

# include <Siv3D/StringView.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/FormatData.hpp>

namespace s3d
{
	std::string StringView::narrow() const
	{
		return Unicode::Narrow(*this);
	}

	std::wstring StringView::toWstr() const
	{
		return Unicode::ToWstring(*this);
	}

	std::string StringView::toUTF8() const
	{
		return Unicode::ToUTF8(*this);
	}

	uint64 StringView::hash() const noexcept
	{
		return Hash::FNV1a(data(), size_bytes());
	}

	std::ostream& operator <<(std::ostream& output, const StringView& value)
	{
		return (output << value.narrow());
	}

	std::wostream& operator <<(std::wostream& output, const StringView& value)
	{
		return (output << value.toWstr());
	}

	std::basic_ostream<char32>& operator <<(std::basic_ostream<char32>& output, const StringView& value)
	{
		return output.write(value.data(), value.size());
	}

	void Formatter(FormatData& formatData, const StringView s)
	{
		formatData.string.append(s);
	}
}
