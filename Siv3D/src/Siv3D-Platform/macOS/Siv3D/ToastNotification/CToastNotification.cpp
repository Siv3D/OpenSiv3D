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

	ToastNotificationID CToastNotification::show(const ToastNotificationItem&)
	{
		// [Siv3D ToDo]
		return(0);
	}

	ToastNotificationState CToastNotification::getState(ToastNotificationID)
	{
		// [Siv3D ToDo]
		return(ToastNotificationState::None_);
	}

	Optional<size_t> CToastNotification::getAction(ToastNotificationID)
	{
		// [Siv3D ToDo]
		return(none);
	}

	void CToastNotification::hide(ToastNotificationID)
	{
		// [Siv3D ToDo]
	}

	void CToastNotification::clear()
	{
		// [Siv3D ToDo]
	}

	void CToastNotification::onStateUpdate(size_t, ToastNotificationState, const Optional<int32>&)
	{
		// [Siv3D ToDo]
	}
}
