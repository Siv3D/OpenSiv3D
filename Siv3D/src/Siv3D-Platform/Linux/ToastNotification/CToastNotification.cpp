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
# include "CToastNotification.hpp"

namespace s3d
{
	CToastNotification::CToastNotification()
	{

	}

	CToastNotification::~CToastNotification()
	{
		clear();

		LOG_TRACE(U"CToastNotification::~CToastNotification()");
	}

	void CToastNotification::init()
	{
		LOG_TRACE(U"CToastNotification::init()");

		LOG_INFO(U"ℹ️ ToastNotification is not available");

		LOG_INFO(U"ℹ️ CToastNotification initialized");
	}

	bool CToastNotification::isAvailable() const
	{
		return(false);
	}

	NotificationID CToastNotification::show(const ToastNotificationProperty&)
	{
		return(-1);
	}

	ToastNotificationState CToastNotification::getState(const NotificationID)
	{
		return(ToastNotificationState::None);
	}

	Optional<size_t> CToastNotification::getAction(const NotificationID)
	{
		return(none);
	}

	void CToastNotification::hide(const NotificationID)
	{

	}

	void CToastNotification::clear()
	{

	}

	void CToastNotification::onStateUpdate(const size_t, const ToastNotificationState, const Optional<int32>&)
	{

	}
}
