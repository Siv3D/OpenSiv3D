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
	}

	Wave CAudioCodec::decode(IReader&, AudioFormat)
	{
		// do nothing
		return{};
	}

	bool CAudioCodec::encode(const Wave& , IWriter&, AudioFormat)
	{
		// do nothing
		return(false);
	}

	Wave CAudioCodec::decode(const FilePathView path, const AudioFormat audioFormat)
	{
		return{};
	}	
}
