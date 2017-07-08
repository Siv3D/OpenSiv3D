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
# include <mutex>
# include <Siv3D/TextWriter.hpp>
# include <Siv3D/Logger.hpp>
# include "ILogger.hpp"

namespace s3d
{
	class CLogger : public ISiv3DLogger
	{
	private:

		TextWriter m_writer;

		std::mutex m_mutex;

		OutputLevel m_outputLevel =

# if defined(_DEBUG) || defined(DEBUG)

			OutputLevel::More;

# else

			OutputLevel::Normal;

# endif

		bool m_initialized = false;

		bool m_hasImportantLog = false;

		bool m_removeFileOnExit = false;

		void outputLicenses();

		bool suppress(LogDescription desc) const;

	public:

		CLogger();

		~CLogger() override;

		bool init() override;

		void setOutputLevel(OutputLevel level) override;

		void write(LogDescription desc, const String& str) override;

		void writeRawHTML(const String& str) override;

		void removeLogOnExit() override;
	};
}
