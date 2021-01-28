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

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "Blob.hpp"

namespace s3d
{
	namespace Base64
	{
		[[nodiscard]]
		String Encode(const void* data, size_t size);

		void Encode(const void* data, size_t size, String& dst);

		void Encode(const void* data, size_t size, std::string& dst);

		[[nodiscard]]
		Blob Decode(StringView base64);

		[[nodiscard]]
		Blob Decode(std::string_view base64);
	}
}
