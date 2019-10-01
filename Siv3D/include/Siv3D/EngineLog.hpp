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
# include "Fwd.hpp"
# include "Format.hpp"
# include "Logger.hpp"

namespace s3d
{
	namespace detail
	{
		void OutputEnginelog(StringView text);
	}
}

# define SIMPLE_LOG(MESSAGE) s3d::detail::OutputEnginelog(MESSAGE)

# if SIV3D_BUILD_TYPE(DEBUG)

#	define LOG_TEST(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Trace,MESSAGE)
#	define LOG_TRACE(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Trace,MESSAGE)
#	define LOG_DEBUG(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Debug,MESSAGE)
#	define LOG_INFO(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Info,MESSAGE)
#	define LOG_WARNING(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Warning,MESSAGE)
#	define LOG_FAIL(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Fail,MESSAGE)
#	define LOG_ERROR(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Error,MESSAGE)
#	define LOG_SCRIPT(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Script,MESSAGE)
#	define LOG_FAIL_ONCE(MESSAGE)	s3d::Logger._outputLogOnce(s3d::LogDescription::Fail,__COUNTER__,MESSAGE)

# elif defined(SIV3D_MINIMUM)

#	define LOG_TRACE(MESSAGE)		((void)0)
#	define LOG_DEBUG(MESSAGE)		((void)0)
#	define LOG_INFO(MESSAGE)		((void)0)
#	define LOG_WARNING(MESSAGE)		((void)0)
#	define LOG_FAIL(MESSAGE)		((void)0)
#	define LOG_ERROR(MESSAGE)		((void)0)
#	define LOG_SCRIPT(MESSAGE)		((void)0)
#	define LOG_FAIL_ONCE(MESSAGE)	((void)0)

# else

#	define LOG_TRACE(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Trace,MESSAGE)
#	define LOG_DEBUG(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Debug,MESSAGE)
#	define LOG_INFO(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Info,MESSAGE)
#	define LOG_WARNING(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Warning,MESSAGE)
#	define LOG_FAIL(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Fail,MESSAGE)
#	define LOG_ERROR(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Error,MESSAGE)
#	define LOG_SCRIPT(MESSAGE)		s3d::Logger._outputLog(s3d::LogDescription::Script,MESSAGE)
#	define LOG_FAIL_ONCE(MESSAGE)	s3d::Logger._outputLogOnce(s3d::LogDescription::Fail,__COUNTER__,MESSAGE)

# endif
