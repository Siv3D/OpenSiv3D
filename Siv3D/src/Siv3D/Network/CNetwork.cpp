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

# include "CNetwork.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Error.hpp>

# define CURL_STATICLIB
# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(MACOS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/curl/curl.h>
# else
#	include <curl/curl.h>
# endif

namespace s3d
{
	CNetwork::CNetwork() {}

	CNetwork::~CNetwork()
	{
		LOG_SCOPED_TRACE(U"CNetwork::~CNetwork()");

		if (m_curlInitialized)
		{
			::curl_global_cleanup();
		}
	}

	void CNetwork::init()
	{
		LOG_SCOPED_TRACE(U"CNetwork::init()");

		if (::CURLE_OK != ::curl_global_init(CURL_GLOBAL_ALL))
		{
			throw EngineError{ U"curl_global_init() failed" };
		}

		m_curlInitialized = true;
	}
}
