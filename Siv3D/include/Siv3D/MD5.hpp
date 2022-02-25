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
# include "MD5Value.hpp"
# include "Blob.hpp"

namespace s3d
{
	namespace MD5
	{
		[[nodiscard]]
		MD5Value FromBinary(const void* const data, size_t size);

		[[nodiscard]]
		MD5Value FromBinary(const Blob& blob);

		[[nodiscard]]
		MD5Value FromText(StringView view);

		[[nodiscard]]
		MD5Value FromText(std::string_view view);

		[[nodiscard]]
		MD5Value FromFile(FilePathView path);
	}
}
