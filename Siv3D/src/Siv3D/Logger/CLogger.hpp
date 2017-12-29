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
# include <Siv3D/HashSet.hpp>
# include "ILogger.hpp"

namespace s3d
{
	class CLogger : public ISiv3DLogger
	{
	private:

		TextWriter m_writer;

		HashSet<uint32> m_onceFlags;

		std::mutex m_mutex;

		OutputLevel m_outputLevel = SIV3D_IS_DEBUG ? OutputLevel::More : OutputLevel::Normal;

		bool m_initialized = false;

		bool m_hasImportantLog = false;

		bool m_removeFileOnExit = false;

		void outputLicenses();

		bool suppressed(LogDescription desc) const;

	public:

		CLogger();

		~CLogger() override;

		bool init() override;

		void setOutputLevel(OutputLevel level) override;

		void write(LogDescription desc, const String& text) override;

		void writeOnce(LogDescription desc, uint32 id, const String& text) override;

		void writeRawHTML(const String& htmlText) override;

		void writeRawHTML_UTF8(std::string_view htmlText) override;

		void removeOnExit() override;
	};
}
