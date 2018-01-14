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
# include <string>
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class ISiv3DLogger
	{
	public:

		static ISiv3DLogger* Create();

		virtual ~ISiv3DLogger() = default;

		virtual bool init() = 0;

		virtual void setOutputLevel(OutputLevel level) = 0;

		virtual void write(LogDescription desc, const String& text) = 0;

		virtual void writeOnce(LogDescription desc, uint32 id, const String& text) = 0;

		virtual void writeRawHTML(const String& htmlText) = 0;

		virtual void writeRawHTML_UTF8(std::string_view htmlText) = 0;

		virtual void removeOnExit() = 0;
	};
}
