//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Fwd.hpp>
# include <Siv3D/String.hpp>

namespace s3d
{
	class ISiv3DAudioFormat
	{
	public:

		static ISiv3DAudioFormat* Create();

		virtual ~ISiv3DAudioFormat() = default;

		virtual bool init() = 0;

		virtual AudioFormat getFormatFromReader(const IReader& reader, const FilePath& pathHint) const = 0;

		virtual AudioFormat getFormatFromFilePath(const FilePath& path) const = 0;

		virtual Wave load(const FilePath& path) const = 0;

		virtual Wave decode(IReader&& reader, AudioFormat format) const = 0;

		virtual bool encodeWAVE(IWriter& writer, const Wave& wave, WAVEFormat format) const = 0;
	};
}
