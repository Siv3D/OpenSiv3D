//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
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

		virtual void write(LogDescription desc, const String& str) = 0;

		virtual void writeRawHTML(const String& str) = 0;

		virtual void removeLogOnExit() = 0;
	};
}
