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
# include <Siv3D/AudioCodec/IAudioCodec.hpp>
# include <mpg123.h>

namespace s3d
{
	class CAudioCodec final : public ISiv3DAudioCodec
	{
	public:

		CAudioCodec();

		~CAudioCodec() override;

		void init() override;
	
		Wave decode(IReader& reader, AudioFormat audioFormat) override;
		
		bool encode(const Wave& wave, IWriter& writer, AudioFormat audioFormat) override;
		
		//
		//	Linux
		//
		
		Wave decode(FilePathView path, AudioFormat audioFormat);

	private:

		void* m_mpg123 = nullptr;
		
		decltype(mpg123_init)* p_mpg123_init = nullptr;
		decltype(mpg123_new)* p_mpg123_new = nullptr;
		decltype(mpg123_delete)* p_mpg123_delete = nullptr;
		decltype(mpg123_exit)* p_mpg123_exit = nullptr;
		decltype(mpg123_param)* p_mpg123_param = nullptr;
		decltype(mpg123_rates)* p_mpg123_rates = nullptr;
		decltype(mpg123_format)* p_mpg123_format = nullptr;
		decltype(mpg123_open_feed)* p_mpg123_open_feed = nullptr;
		decltype(mpg123_feed)* p_mpg123_feed = nullptr;
		decltype(mpg123_decode_frame)* p_mpg123_decode_frame = nullptr;
		decltype(mpg123_getformat)* p_mpg123_getformat = nullptr;
		decltype(mpg123_scan)* p_mpg123_scan = nullptr;
		decltype(mpg123_length)* p_mpg123_length = nullptr;
		decltype(mpg123_open)* p_mpg123_open = nullptr;
		decltype(mpg123_replace_reader_handle)* p_mpg123_replace_reader_handle = nullptr;
		decltype(mpg123_open_handle)* p_mpg123_open_handle = nullptr;
		decltype(mpg123_close)* p_mpg123_close = nullptr;
		decltype(mpg123_info)* p_mpg123_info = nullptr;
		
		bool m_libmpg123Available = false;

		void loadMPG123();

		Wave decodeMP3(IReader& reader);
	};
}
