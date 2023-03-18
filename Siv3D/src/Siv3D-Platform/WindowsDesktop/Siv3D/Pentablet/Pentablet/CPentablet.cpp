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

# include "CPentablet.hpp"
# include <Siv3D/DLL.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static double GetValue(const int32 value, const AXIS& caps)
		{
			if (const auto range = (caps.axMax - caps.axMin))
			{
				return (static_cast<double>(value) / caps.axMax);
			}
			else
			{
				return 0.0;
			}
		}
	}

	CPentablet::CPentablet()
	{

	}

	CPentablet::~CPentablet()
	{
		LOG_SCOPED_TRACE(U"CPentablet::~CPentablet()");

		if (m_hCtx && p_WTClose)
		{
			p_WTClose(nullptr);
		}

		DLL::Unload(m_wintab);
	}

	void CPentablet::init()
	{
		LOG_SCOPED_TRACE(U"CPentablet::init()");
	}

	void CPentablet::update()
	{
		if (not m_wintabAvailable)
		{
			return;
		}

		const int32 queueSize = p_WTQueueSizeGet(m_hCtx);
		m_packetsBuffer.resize(queueSize);

		if (const int32 n = p_WTPacketsGet(m_hCtx, static_cast<int32>(m_packetsBuffer.size()), m_packetsBuffer.data()))
		{
			//for (int32 i = 0; i < n; ++i)
			//{
			//	if (m_packetsBuffer[i].pkButtons)
			//	{
			//		LOG_TRACE(U"{}"_fmt(m_packetsBuffer[i].pkButtons));
			//	}
			//}

			const auto& packet = m_packetsBuffer[n - 1];

			if (m_state.supportPressure)
			{
				m_state.pressure = detail::GetValue(packet.pkNormalPressure, m_pressureCaps);
			}

			if (m_state.supportTangentPressure)
			{
				m_state.tangentPressure = detail::GetValue(packet.pkTangentPressure, m_tangentPressureCaps);
			}

			if (m_state.supportOrientation)
			{
				m_state.azimuth = detail::GetValue(packet.pkOrientation.orAzimuth, m_azimuthCaps);
				m_state.altitude = detail::GetValue(packet.pkOrientation.orAltitude, m_altitudeCaps);
				m_state.twist = detail::GetValue(packet.pkOrientation.orTwist, m_twistCaps);
			}
		}
	}

	bool CPentablet::isAvailable()
	{
		if (not m_initialized)
		{
			init2();
		}

		return m_wintabAvailable;
	}

	const PentabletState& CPentablet::getState()
	{
		if (not m_initialized)
		{
			init2();
		}

		return m_state;
	}

	void CPentablet::init2()
	{
		assert(not m_initialized);

		m_initialized = true;

		m_wintab = DLL::LoadSystemLibraryNoThrow(L"Wintab32.dll");

		if (not m_wintab)
		{
			LOG_INFO(U"ℹ️ Wintab is not available");
			return;
		}

		p_WTInfoW = DLL::GetFunctionNoThrow(m_wintab, "WTInfoW");
		p_WTClose = DLL::GetFunctionNoThrow(m_wintab, "WTClose");
		p_WTOpenW = DLL::GetFunctionNoThrow(m_wintab, "WTOpenW");
		p_WTQueueSizeGet = DLL::GetFunctionNoThrow(m_wintab, "WTQueueSizeGet");
		p_WTPacketsGet = DLL::GetFunctionNoThrow(m_wintab, "WTPacketsGet");

		if ((not p_WTInfoW)
			|| (not p_WTClose)
			|| (not p_WTOpenW)
			|| (not p_WTQueueSizeGet)
			|| (not p_WTPacketsGet))
		{
			LOG_INFO(U"ℹ️ Failed to load Wintab functions");
			return;
		}

		{
			wchar_t name[256] = {};
			if (not p_WTInfoW(WTI_DEVICES, DVC_NAME, name))
			{
				LOG_INFO(U"✖ WTInfoW(WTI_DEVICES, DVC_NAME) failed");
				return;
			}

			LOG_INFO(U"ℹ️ Pentablet: `{}`"_fmt(Unicode::FromWstring(name)));
		}

		{
			m_state.supportPressure = (p_WTInfoW(WTI_DEVICES, DVC_NPRESSURE, &m_pressureCaps) > 0);
			m_state.supportTangentPressure = (p_WTInfoW(WTI_DEVICES, DVC_TPRESSURE, &m_tangentPressureCaps) > 0);

			AXIS orientationCaps[3];
			m_state.supportOrientation = (p_WTInfoW(WTI_DEVICES, DVC_ORIENTATION, &orientationCaps) > 0);

			if (m_state.supportPressure)
			{
				LOG_INFO(U"ℹ️ Pressure: min = {}, max = {}"_fmt(m_pressureCaps.axMin, m_pressureCaps.axMax));
			}

			if (m_state.supportTangentPressure)
			{
				LOG_INFO(U"ℹ️ TangentPressure: min = {}, max = {}"_fmt(m_tangentPressureCaps.axMin, m_tangentPressureCaps.axMax));
			}

			if (m_state.supportOrientation)
			{
				m_azimuthCaps = orientationCaps[0];
				m_altitudeCaps = orientationCaps[1];
				m_twistCaps = orientationCaps[2];

				LOG_INFO(U"ℹ️ Azimuth: min = {}, max = {}"_fmt(m_azimuthCaps.axMin, m_azimuthCaps.axMax));
				LOG_INFO(U"ℹ️ Altitude: min = {}, max = {}"_fmt(m_altitudeCaps.axMin, m_altitudeCaps.axMax));
				LOG_INFO(U"ℹ️ Twist: min = {}, max = {}"_fmt(m_twistCaps.axMin, m_twistCaps.axMax));
			}
		}

		{
			LOGCONTEXTW context;

			if (not p_WTInfoW(WTI_DEFCONTEXT, 0, &context))
			{
				LOG_INFO(U"✖ WTInfoW(WTI_DEFCONTEXT, 0) failed");
				return;
			}

			::wsprintfW(context.lcName, L"Siv3D Wintab %p", ::GetModuleHandleW(nullptr));
			context.lcOptions |= CXO_SYSTEM;
			context.lcPktData = PACKETDATA;
			context.lcPktMode = PACKETMODE;
			context.lcMoveMask = PACKETDATA;
			context.lcBtnUpMask = context.lcBtnDnMask;

			HWND hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());
			m_hCtx = p_WTOpenW(hWnd, &context, TRUE);

			if (not m_hCtx)
			{
				LOG_INFO(U"✖ WTOpenW() failed");
				return;
			}
		}

		const int32 queueSize = p_WTQueueSizeGet(m_hCtx);
		LOG_INFO(U"ℹ️ Wintab is available (Queue size: {})"_fmt(queueSize));

		m_wintabAvailable = true;
	}
}
