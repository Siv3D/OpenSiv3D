//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Error.hpp>
# include <Siv3D/DLL.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CAudioCodec.hpp"

namespace s3d
{
	CAudioCodec::CAudioCodec()
	{
		// do nothing
	}

	CAudioCodec::~CAudioCodec()
	{
		LOG_SCOPED_TRACE(U"CAudioCodec::~CAudioCodec()");
	}

	void CAudioCodec::init()
	{
		LOG_SCOPED_TRACE(U"CAudioCodec::init()");

		loadMPG123();
	}

	Wave CAudioCodec::decode(IReader&, AudioFormat audioFormat)
	{
		if (audioFormat = AudioFormat::MP3)
		{

		}
		else if (audioFormat = AudioFormat::AAC)
		{

		}

		// do nothing
		return{};
	}

	bool CAudioCodec::encode(const Wave& , IWriter&, AudioFormat)
	{
		// do nothing
		return(false);
	}

	void CAudioCodec::loadMPG123()
	{
		LOG_SCOPED_TRACE(U"CAudioCodec::loadMPG123()");

		const FilePath libPath = U"libmpg123.so"; //Resource(U"engine/lib/mpg123/libmpg123.so");
		
		m_mpg123 = DLL::LoadLibrary(libPath.narrow().c_str());
		
		if (not m_mpg123)
		{
			LOG_FAIL(U"❌ Failed to load \"{0}\""_fmt(libPath));
			return;
		}
		
		p_mpg123_init = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_init");
		p_mpg123_new = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_new");
		p_mpg123_delete = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_delete");
		p_mpg123_exit = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_exit");
		p_mpg123_param = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_param");
		p_mpg123_rates = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_rates");
		p_mpg123_format = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_format");
		p_mpg123_open_feed = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_open_feed");
		p_mpg123_feed = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_feed");
		p_mpg123_decode_frame = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_decode_frame");
		p_mpg123_getformat = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_getformat");
		p_mpg123_scan = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_scan");
		p_mpg123_length = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_length");
		p_mpg123_open = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_open");
		p_mpg123_open_handle = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_open_handle");
		p_mpg123_replace_reader_handle = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_replace_reader_handle");
		p_mpg123_close = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_close");
		p_mpg123_info = DLL::GetFunctionNoThrow(m_mpg123, "mpg123_info");
		
		if (!(p_mpg123_init && p_mpg123_new && p_mpg123_delete && p_mpg123_exit && p_mpg123_param
			&& p_mpg123_rates && p_mpg123_format && p_mpg123_open_feed && p_mpg123_feed
			&& p_mpg123_decode_frame && p_mpg123_getformat && p_mpg123_scan && p_mpg123_length
			&& p_mpg123_open && p_mpg123_open_handle && p_mpg123_replace_reader_handle
			&& p_mpg123_info))
		{
			return;
		}
		
		if (p_mpg123_init() != MPG123_OK)
		{
			p_mpg123_exit = nullptr;		
			return;
		}
		
		m_libmpg123Available = true;
		LOG_INFO(U"libmpg123 is available");
	}
}
