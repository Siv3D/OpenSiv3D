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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Pentablet/IPentablet.hpp>
# include <Siv3D/Windows/Windows.hpp>

# define PACKETDATA	(PK_NORMAL_PRESSURE | PK_TANGENT_PRESSURE | PK_ORIENTATION | PK_BUTTONS)
# define PACKETMODE	PK_BUTTONS
# include <ThirdParty/Wintab/MSGPACK.H>
# include <ThirdParty/Wintab/WINTAB.H>
# include <ThirdParty/Wintab/PKTDEF.H>

namespace s3d
{
	class CPentablet final : public ISiv3DPentablet
	{
	public:

		CPentablet();

		~CPentablet() override;

		void init() override;

		void update() override;

		bool isAvailable() override;

		const PentabletState& getState() override;

	private:

		HINSTANCE m_wintab = nullptr;
		HCTX m_hCtx = nullptr;
		Array<PACKET> m_packetsBuffer;

		decltype(WTInfoW)* p_WTInfoW = nullptr;
		decltype(WTClose)* p_WTClose = nullptr;
		decltype(WTOpenW)* p_WTOpenW = nullptr;
		decltype(WTQueueSizeGet)* p_WTQueueSizeGet = nullptr;
		decltype(WTPacketsGet)* p_WTPacketsGet = nullptr;

		bool m_initialized = false;
		bool m_wintabAvailable = false;

		AXIS m_pressureCaps = {};
		AXIS m_tangentPressureCaps = {};
		AXIS m_azimuthCaps = {};
		AXIS m_altitudeCaps = {};
		AXIS m_twistCaps = {};

		PentabletState m_state;

		void init2();
	};
}
