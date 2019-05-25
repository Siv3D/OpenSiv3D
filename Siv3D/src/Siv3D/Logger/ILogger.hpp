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

# pragma once
# include <string>
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class ISiv3DLogger
	{
	public:

		static ISiv3DLogger* Create();

		virtual ~ISiv3DLogger() = default;

		virtual void setOutputLevel(OutputLevel level) = 0;

		virtual void write(LogDescription desc, const String& text) = 0;

		virtual void writeOnce(LogDescription desc, uint32 id, const String& text) = 0;

		virtual void writeRawHTML_UTF8(std::string_view htmlText) = 0;
	};
}
