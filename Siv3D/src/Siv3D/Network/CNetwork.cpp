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

# include "CNetwork.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Error.hpp>

# define CURL_STATICLIB
# if SIV3D_PLATFORM(WINDOWS)
#	include <ThirdParty-prebuilt/curl/curl.h>
# elif SIV3D_PLATFORM(WEB)
#   // 何もインクルードしない
# else
#	include <curl/curl.h>
# endif

namespace s3d
{
	CNetwork::CNetwork() {}

	CNetwork::~CNetwork()
	{
		LOG_SCOPED_TRACE(U"CNetwork::~CNetwork()");

# if not SIV3D_PLATFORM(WEB)

		if (m_curlInitialized)
		{
			::curl_global_cleanup();
		}

# endif
	}

	void CNetwork::init()
	{
		if (m_curlInitialized)
		{
			return;
		}

		LOG_SCOPED_TRACE(U"CNetwork::init()");

# if not SIV3D_PLATFORM(WEB)

		if (::CURLE_OK != ::curl_global_init(CURL_GLOBAL_ALL))
		{
			throw EngineError{ U"curl_global_init() failed" };
		}

# endif

		m_curlInitialized = true;
	}
}
