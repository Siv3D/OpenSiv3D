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

# include "CToastNotification.hpp"

namespace s3d
{
	namespace detail
	{
		using siv3dRequestNotificationPermissionCallback = void(*)(CToastNotification::NotificationPermission, void* userData);
	
		__attribute__((import_name("siv3dRequestNotificationPermission")))
		extern void siv3dRequestNotificationPermission(siv3dRequestNotificationPermissionCallback callback, void* userData);

		void OnRequestNotificationPermission(CToastNotification::NotificationPermission permission, void* userData)
		{
			auto p = static_cast<std::promise<bool>*>(userData);

			p->set_value(permission == CToastNotification::NotificationPermission::Granted);
			delete p;
		}
	}

	namespace Platform::Web::Notification
	{
		AsyncTask<bool> RequestPermission()
		{
			auto p = new std::promise<bool>();
			auto asyncResult = p->get_future();

			detail::siv3dRequestNotificationPermission(&detail::OnRequestNotificationPermission, p);
			return asyncResult;
		}
	}
}