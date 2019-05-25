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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Wave.hpp>
# include "CCodec.hpp"

namespace s3d
{
	CCodec::CCodec()
	{
		
	}
	
	CCodec::~CCodec()
	{
		LOG_TRACE(U"CCodec::~CCodec()");
	}
	
	void CCodec::init()
	{
		LOG_TRACE(U"CCodec::init()");
		
		LOG_INFO(U"ℹ️ CCodec initialized");
	}
	
	Wave CCodec::decode(IReader&)
	{
		// [Siv3D ToDo]
		return Wave();
	}
}
