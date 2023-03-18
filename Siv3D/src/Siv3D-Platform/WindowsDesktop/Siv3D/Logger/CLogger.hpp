//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <atomic>
# include <mutex>
# include <Siv3D/Logger/ILogger.hpp>

namespace s3d
{
	class CLogger final : public ISiv3DLogger
	{
	private:

		std::mutex m_mutex;

		std::atomic<bool> m_enabled{ true };

	public:

		CLogger();

		~CLogger() override;

		void write(LogType type, StringView s) override;

		void setEnabled(bool enabled) override;
	};
}
