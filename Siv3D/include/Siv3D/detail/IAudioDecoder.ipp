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

namespace s3d
{
	inline Wave IAudioDecoder::decode(const FilePathView path) const
	{
		BinaryReader reader{ path };

		if (not reader)
		{
			return{};
		}

		return decode(reader, path);
	}
}
