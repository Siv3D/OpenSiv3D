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
# include "Common.hpp"
# include "LogType.hpp"
# include "StringView.hpp"
# include "String.hpp"
# include "FormatLiteral.hpp"
# include "detail/EngineLog.ipp"

# if SIV3D_BUILD(DEBUG)

#	define LOG_TEST(S)		s3d::Internal::OutputEngineLog(s3d::LogType::App,		S)
#	define LOG_ERROR(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Error,		S)
#	define LOG_FAIL(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Fail,		S)
#	define LOG_WARNING(S)	s3d::Internal::OutputEngineLog(s3d::LogType::Warning,	S)
#	define LOG_INFO(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Info,		S)
#	define LOG_TRACE(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Trace,		S)
#	define LOG_VERBOSE(S)	s3d::Internal::OutputEngineLog(s3d::LogType::Verbose,	S)
#	define LOG_SCOPED_TRACE(S)	const s3d::Internal::ScopedEngineLog s3d_scoped_trace{s3d::LogType::Trace, S}

# elif SIV3D_PLATFORM(WEB)

#	define LOG_ERROR(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Error,		S)
#	define LOG_FAIL(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Fail,		S)
#	define LOG_WARNING(S)	s3d::Internal::OutputEngineLog(s3d::LogType::Warning,	S)
#	define LOG_INFO(S)		((void)0)
#	define LOG_TRACE(S)		((void)0)
#	define LOG_VERBOSE(S)	((void)0)
#	define LOG_SCOPED_TRACE(S)	((void)0)

# else

#	define LOG_ERROR(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Error,		S)
#	define LOG_FAIL(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Fail,		S)
#	define LOG_WARNING(S)	s3d::Internal::OutputEngineLog(s3d::LogType::Warning,	S)
#	define LOG_INFO(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Info,		S)
#	define LOG_TRACE(S)		((void)0)
#	define LOG_VERBOSE(S)	((void)0)
#	define LOG_SCOPED_TRACE(S)	((void)0)

# endif
