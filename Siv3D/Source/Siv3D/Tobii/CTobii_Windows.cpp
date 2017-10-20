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

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include "CTobii_Windows.hpp"
# include "../EngineUtility.hpp"
# include "../Siv3DEngine.hpp"
# include "../Window/IWindow.hpp"
# include <Siv3D/Window.hpp>
# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		const std::array<std::pair<tobii_stream_t, String>, 9> TobiiStreamTypes =
		{ {
			{ TOBII_STREAM_GAZE_POINT, L"TOBII_STREAM_GAZE_POINT" },
			{ TOBII_STREAM_GAZE_ORIGIN, L"TOBII_STREAM_GAZE_ORIGIN" },
			{ TOBII_STREAM_EYE_POSITION_NORMALIZED, L"TOBII_STREAM_EYE_POSITION_NORMALIZED" },
			{ TOBII_STREAM_USER_PRESENCE, L"TOBII_STREAM_USER_PRESENCE" },
			{ TOBII_STREAM_HEAD_POSE, L"TOBII_STREAM_HEAD_POSE" },
			{ TOBII_STREAM_WEARABLE, L"TOBII_STREAM_WEARABLE" },
			{ TOBII_STREAM_GAZE_DATA, L"TOBII_STREAM_GAZE_DATA" },
			{ TOBII_STREAM_DIGITAL_SYNCPORT, L"TOBII_STREAM_DIGITAL_SYNCPORT" },
			{ TOBII_STREAM_DIAGNOSTICS_IMAGE, L"TOBII_STREAM_DIAGNOSTICS_IMAGE" },
		} };
	}

	Tobii::CTobii::CTobii(const FilePath& dllPath)
		: m_tobii(::LoadLibraryW(dllPath.c_str()))
	{
		if (!m_tobii)
		{
			LOG_FAIL(L"❌ Tobii software component `{}` is not found"_fmt(dllPath));
			return;
		}

		p_tobii_api_create = FunctionPointer(m_tobii, "tobii_api_create");
		p_tobii_device_create = FunctionPointer(m_tobii, "tobii_device_create");
		p_tobii_device_destroy = FunctionPointer(m_tobii, "tobii_device_destroy");
		p_tobii_api_destroy = FunctionPointer(m_tobii, "tobii_api_destroy");
		p_tobii_reconnect = FunctionPointer(m_tobii, "tobii_reconnect");
		p_tobii_get_device_info = FunctionPointer(m_tobii, "tobii_get_device_info");
		p_tobii_stream_supported = FunctionPointer(m_tobii, "tobii_stream_supported");
		p_tobii_gaze_point_subscribe = FunctionPointer(m_tobii, "tobii_gaze_point_subscribe");
		p_tobii_gaze_point_unsubscribe = FunctionPointer(m_tobii, "tobii_gaze_point_unsubscribe");
		p_tobii_gaze_origin_subscribe = FunctionPointer(m_tobii, "tobii_gaze_origin_subscribe");
		p_tobii_gaze_origin_unsubscribe = FunctionPointer(m_tobii, "tobii_gaze_origin_unsubscribe");
		p_tobii_user_presence_subscribe = FunctionPointer(m_tobii, "tobii_user_presence_subscribe");
		p_tobii_user_presence_unsubscribe = FunctionPointer(m_tobii, "tobii_user_presence_unsubscribe");
		p_tobii_process_callbacks = FunctionPointer(m_tobii, "tobii_process_callbacks");

		if (!p_tobii_api_create || !p_tobii_device_create || !p_tobii_device_destroy || !p_tobii_api_destroy
			|| !p_tobii_reconnect || !p_tobii_get_device_info || !p_tobii_stream_supported
			|| !p_tobii_gaze_point_subscribe || !p_tobii_gaze_point_unsubscribe
			|| !p_tobii_gaze_origin_subscribe || !p_tobii_gaze_origin_unsubscribe
			|| !p_tobii_user_presence_subscribe || !p_tobii_user_presence_unsubscribe
			|| !p_tobii_process_callbacks)
		{
			LOG_FAIL(L"❌ Tobii: Failed to load functions");
			return;
		}

		if (p_tobii_api_create(&m_api, nullptr, nullptr) != TOBII_ERROR_NO_ERROR)
		{
			LOG_FAIL(L"❌ Tobii: tobii_api_create() failed");
			return;
		}

		m_initialized = true;

		reconnect();
	}

	Tobii::CTobii::~CTobii()
	{
		if (m_device)
		{
			p_tobii_user_presence_unsubscribe(m_device);
			p_tobii_gaze_origin_unsubscribe(m_device);
			p_tobii_gaze_point_unsubscribe(m_device);
			p_tobii_device_destroy(m_device);

			LOG_DEBUG(L"Tobii: device shut down");
		}

		if (m_api)
		{
			p_tobii_api_destroy(m_api);
		}

		::FreeLibrary(m_tobii);
	}

	bool Tobii::CTobii::reconnect()
	{
		if (tobii_error_t error = p_tobii_device_create(m_api, nullptr, &m_device); error == TOBII_ERROR_NO_ERROR)
		{
			tobii_device_info_t info = {};

			if (p_tobii_get_device_info(m_device, &info) == TOBII_ERROR_NO_ERROR)
			{
				LOG_INFO(L"ℹ️ Tobii device connected: {} ({})"_fmt(CharacterSet::Widen(info.model), CharacterSet::Widen(info.generation)));
			}

			bool features[detail::TobiiStreamTypes.size()] = {};
			{
				Array<String> supportedFeatures;

				tobii_supported_t supported;

				for (size_t i = 0; i < detail::TobiiStreamTypes.size(); ++i)
				{
					const auto& streamType = detail::TobiiStreamTypes[i];

					if (p_tobii_stream_supported(m_device, streamType.first, &supported) == TOBII_ERROR_NO_ERROR
						&& supported == TOBII_SUPPORTED)
					{
						features[i] = true;

						supportedFeatures.push_back(streamType.second);
					}
				}

				LOG_INFO(L"ℹ️ Supported features: {}"_fmt(supportedFeatures));
			}
				
			if (features[TOBII_STREAM_GAZE_POINT])
			{
				if (error = p_tobii_gaze_point_subscribe(m_device, gaze_point_callback, this);
					error != TOBII_ERROR_NO_ERROR && error != TOBII_ERROR_ALREADY_SUBSCRIBED)
				{
					LOG_FAIL(L"❌ Tobii: tobii_gaze_point_subscribe() failed");
				}
			}

			if (features[TOBII_STREAM_GAZE_ORIGIN])
			{
				if (error = p_tobii_gaze_origin_subscribe(m_device, gaze_origin_callback, this);
					error != TOBII_ERROR_NO_ERROR && error != TOBII_ERROR_ALREADY_SUBSCRIBED)
				{
					LOG_FAIL(L"❌ Tobii: tobii_gaze_origin_subscribe() failed");
				}
			}

			if (features[TOBII_STREAM_USER_PRESENCE])
			{
				if (error = p_tobii_user_presence_subscribe(m_device, presence_callback, this);
					error != TOBII_ERROR_NO_ERROR && error != TOBII_ERROR_ALREADY_SUBSCRIBED)
				{
					LOG_FAIL(L"❌ Tobii: tobii_user_presence_subscribe() failed");
				}
			}

			m_connected = true;
		}
		else
		{
			if (error == TOBII_ERROR_NOT_AVAILABLE)
			{
				LOG_FAIL(L"❌ Tobii device is not found");
			}

			m_connected = false;
		}

		return m_connected;
	}

	bool Tobii::CTobii::isInitialized() const noexcept
	{
		return m_initialized;
	}

	bool Tobii::CTobii::isConnected() const noexcept
	{
		return m_connected;
	}

	bool Tobii::CTobii::hasNewFrame()
	{
		if (!m_connected)
		{
			return false;
		}
		
		if (tobii_error_t error = p_tobii_process_callbacks(m_device); error != TOBII_ERROR_NO_ERROR)
		{
			LOG_INFO(L"ℹ️ Tobii device is disconnected");

			m_hasNewFrame = false;

			m_connected = false;
		}
		
		return m_hasNewFrame;
	}

	bool Tobii::CTobii::getFrame(GazeInfo& info)
	{
		if (!hasNewFrame())
		{
			return false;
		}

		info = m_gazeInfo;
		
		m_hasNewFrame = false;

		return true;
	}

	void Tobii::CTobii::gaze_point_callback(tobii_gaze_point_t const* gazePoint, void* userData)
	{
		CTobii* pTobii = static_cast<CTobii*>(userData);

		pTobii->onGazePoint(
			gazePoint->validity ? Vec2(gazePoint->position_xy[0], gazePoint->position_xy[1]) : Optional<Vec2>());
	}

	void Tobii::CTobii::gaze_origin_callback(const tobii_gaze_origin_t* gazeOrigin, void* userData)
	{
		CTobii* pTobii = static_cast<CTobii*>(userData);

		pTobii->onGazeOrigin(
			gazeOrigin->left_validity ? Vec3(gazeOrigin->left_xyz[0], gazeOrigin->left_xyz[1], gazeOrigin->left_xyz[2]) : Optional<Vec3>(),
			gazeOrigin->right_validity ? Vec3(gazeOrigin->right_xyz[0], gazeOrigin->right_xyz[1], gazeOrigin->right_xyz[2]) : Optional<Vec3>()
		);
	}

	void Tobii::CTobii::presence_callback(const tobii_user_presence_status_t status, std::int64_t, void* userData)
	{
		CTobii* pTobii = static_cast<CTobii*>(userData);

		pTobii->onPresence(status == TOBII_USER_PRESENCE_STATUS_PRESENT);
	}

	void Tobii::CTobii::onGazePoint(const Optional<Vec2>& pos)
	{
		if (pos)
		{
			m_gazeInfo.rawPos = pos.value();

			m_gazeInfo.screenPos = m_gazeInfo.rawPos * Window::GetState().screenSize;

			POINT clientPos{ static_cast<int32>(m_gazeInfo.screenPos.x), static_cast<int32>(m_gazeInfo.screenPos.y) };

			::ScreenToClient(Siv3DEngine::GetWindow()->getHandle(), &clientPos);

			m_gazeInfo.clientPos.set(clientPos.x, clientPos.y);

			m_gazeInfo.clientPos = Graphics2D::GetTransformScreen().inversed().transform(m_gazeInfo.clientPos);
		}

		m_gazeInfo.posValidity = pos.has_value();

		m_hasNewFrame = true;
	}

	void Tobii::CTobii::onGazeOrigin(const Optional<Vec3>& left, const Optional<Vec3>& right)
	{
		if (left)
		{
			m_gazeInfo.leftEyePos = left.value();
		}

		if (right)
		{
			m_gazeInfo.rightEyePos = right.value();
		}

		m_gazeInfo.leftEyePosValidity = left.has_value();

		m_gazeInfo.rightEyePosValidity = right.has_value();

		m_hasNewFrame = true;
	}

	void Tobii::CTobii::onPresence(const bool presence)
	{
		m_gazeInfo.userPresence = presence;

		m_hasNewFrame = true;
	}
}

# endif
