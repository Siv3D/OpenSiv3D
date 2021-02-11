//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/StringView.hpp>
# include <Siv3D/Unicode.hpp>

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
}
