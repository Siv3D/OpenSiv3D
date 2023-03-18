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

# include "SystemMisc.hpp"
# include <Siv3D/EngineLog.hpp>
# include <ThirdParty/Oniguruma/oniguruma.h>

namespace s3d
{
	namespace SystemMisc
	{
		void Init()
		{
			LOG_SCOPED_TRACE(U"SystemMisc::Init()");

			// Oniguruma
			{
				LOG_TRACE(U"Initializing Oniguruma");
				OnigEncoding use_encs = ONIG_ENCODING_UTF32_LE;
				onig_initialize(&use_encs, 1);
			}
		}

		void Destroy()
		{
			LOG_SCOPED_TRACE(U"SystemMisc::Destroy()");

			// Oniguruma
			{
				LOG_TRACE(U"Destroying Oniguruma");
				onig_end();
			}
		}
	}
}

