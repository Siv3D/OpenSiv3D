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

# include <Siv3D/EngineLog.hpp>
# include "CToastNotification.hpp"

namespace s3d
{
	CToastNotification::CToastNotification() {}

	CToastNotification::~CToastNotification()
	{
		LOG_SCOPED_TRACE(U"CToastNotification::~CToastNotification()");
	}

	void CToastNotification::init()
	{
		LOG_SCOPED_TRACE(U"CToastNotification::init()");
	}

	bool CToastNotification::isAvailable() const
	{
		// [Siv3D ToDo]
		return false;
	}

	NotificationID CToastNotification::show(const ToastNotificationItem& item)
	{
		// [Siv3D ToDo]
		return(0);
	}

	ToastNotificationState CToastNotification::getState(NotificationID id)
	{
		// [Siv3D ToDo]
		return(ToastNotificationState::_None);
	}

	Optional<size_t> CToastNotification::getAction(NotificationID id)
	{
		// [Siv3D ToDo]
		return(none);
	}

	void CToastNotification::hide(NotificationID id)
	{
		// [Siv3D ToDo]
	}

	void CToastNotification::clear()
	{
		// [Siv3D ToDo]
	}

	void CToastNotification::onStateUpdate(size_t index, ToastNotificationState state, const Optional<int32>& option)
	{
		// [Siv3D ToDo]
	}
}
