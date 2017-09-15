//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include <Siv3D/Logger.hpp>

namespace s3d
{
	class Tobii::CTobii
	{
	private:

	public:

		explicit CTobii(const FilePath&)
		{
			LOG_FAIL(L"❌ Tobii is not supported on macOS");
		}

		~CTobii()
		{

		}

		bool reconnect()
		{
			return false;
		}

		bool isInitialized() const noexcept
		{
			return false;
		}

		bool isConnected() const noexcept
		{
			return false;
		}

		bool hasNewFrame()
		{
			return false;
		}

		bool getFrame(GazeInfo&)
		{
			return false;
		}
	};
}

# endif
