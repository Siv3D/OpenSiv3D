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
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <Siv3D/Tobii.hpp>
# include <Siv3D/Optional.hpp>
# include <Siv3D/PointVector.hpp>
# include "../../../ThirdParty/tobii/tobii.h"
# include "../../../ThirdParty/tobii/tobii_streams.h"

namespace s3d
{
	class Tobii::CTobii
	{
	private:

		HINSTANCE m_tobii = nullptr;

		tobii_api_t* m_api = nullptr;

		tobii_device_t* m_device = nullptr;

		GazeInfo m_gazeInfo;

		decltype(tobii_api_create)* p_tobii_api_create = nullptr;
		decltype(tobii_device_create)* p_tobii_device_create = nullptr;
		decltype(tobii_device_destroy)* p_tobii_device_destroy = nullptr;
		decltype(tobii_api_destroy)* p_tobii_api_destroy = nullptr;
		decltype(tobii_reconnect)* p_tobii_reconnect = nullptr;
		decltype(tobii_get_device_info)* p_tobii_get_device_info = nullptr;
		decltype(tobii_stream_supported)* p_tobii_stream_supported = nullptr;

		decltype(tobii_gaze_point_subscribe)* p_tobii_gaze_point_subscribe = nullptr;
		decltype(tobii_gaze_point_unsubscribe)* p_tobii_gaze_point_unsubscribe = nullptr;

		decltype(tobii_gaze_origin_subscribe)* p_tobii_gaze_origin_subscribe = nullptr;
		decltype(tobii_gaze_origin_unsubscribe)* p_tobii_gaze_origin_unsubscribe = nullptr;
		
		decltype(tobii_user_presence_subscribe)* p_tobii_user_presence_subscribe = nullptr;
		decltype(tobii_user_presence_unsubscribe)* p_tobii_user_presence_unsubscribe = nullptr;

		decltype(tobii_process_callbacks)* p_tobii_process_callbacks = nullptr;

		bool m_initialized = false;

		bool m_connected = false;

		bool m_hasNewFrame = false;

		static void gaze_point_callback(const tobii_gaze_point_t* gazePoint, void* userData);

		static void gaze_origin_callback(const tobii_gaze_origin_t* gazeOrigin, void* userData);

		static void presence_callback(tobii_user_presence_status_t status, std::int64_t timestamp_us, void* userData);

		void onGazePoint(const Optional<Vec2>& pos);

		void onGazeOrigin(const Optional<Vec3>& left, const Optional<Vec3>& right);

		void onPresence(bool presence);

	public:

		explicit CTobii(const FilePath& dllPath);

		~CTobii();

		bool reconnect();

		bool isInitialized() const noexcept;

		bool isConnected() const noexcept;

		bool hasNewFrame();

		bool getFrame(GazeInfo& info);
	};
}

# endif
