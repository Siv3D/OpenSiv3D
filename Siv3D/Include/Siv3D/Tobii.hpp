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
# include <memory>
# include "Fwd.hpp"
# include "String.hpp"
# include "PointVector.hpp"

namespace s3d
{
# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)

	# define S3D_TOBII_DEFAULT_DLL_PATH	S3DSTR("dll_x86/tobii/tobii_stream_engine.dll")

# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)

	# define S3D_TOBII_DEFAULT_DLL_PATH S3DSTR("dll_x64/tobii/tobii_stream_engine.dll")

# else

	# define S3D_TOBII_DEFAULT_DLL_PATH S3DSTR("")

# endif

	struct GazeInfo
	{
		Vec2 rawPos = Vec2(0.0, 0.0);

		Vec2 screenPos = Vec2(0.0, 0.0);

		Vec2 clientPos = Vec2(0, 0);

		Vec3 leftEyePos = Vec3(0, 0, 0);

		Vec3 rightEyePos = Vec3(0, 0, 0);

		bool userPresence = false;

		bool posValidity = false;

		bool leftEyePosValidity = false;

		bool rightEyePosValidity = false;
	};

	class Tobii
	{
	private:

		class CTobii;

		std::shared_ptr<CTobii> pImpl;

	public:

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		explicit Tobii(const FilePath& dllPath = S3D_TOBII_DEFAULT_DLL_PATH);

		~Tobii();

		bool isInitialized() const;

		explicit operator bool() const
		{
			return isInitialized();
		}

		bool isConnected() const;

		bool reconnect();

		bool hasNewFrame();

		bool getFrame(GazeInfo& info);
	};
}
