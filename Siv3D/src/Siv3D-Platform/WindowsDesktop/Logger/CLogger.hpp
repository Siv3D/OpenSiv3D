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
# include <mutex>
# include <Siv3D/TextWriter.hpp>
# include <Siv3D/Logger.hpp>
# include <Siv3D/HashSet.hpp>
# include <Logger/ILogger.hpp>

namespace s3d
{
	class CLogger : public ISiv3DLogger
	{
	private:

		std::string m_buffer;

		HashSet<uint32> m_onceFlags;

		std::mutex m_mutex;

		OutputLevel m_outputLevel = SIV3D_BUILD_TYPE(DEBUG) ? OutputLevel::More : OutputLevel::Normal;

		bool m_active = true;

		bool m_hasImportantLog = false;

	public:

		CLogger();

		~CLogger() override;

		void setOutputLevel(OutputLevel level) override;

		void write(LogDescription desc, const String& text) override;

		void writeOnce(LogDescription desc, uint32 id, const String& text) override;

		void writeRawHTML_UTF8(std::string_view htmlText) override;
	};
}
