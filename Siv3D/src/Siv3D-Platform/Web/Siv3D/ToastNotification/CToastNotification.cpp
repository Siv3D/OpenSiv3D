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
	namespace detail
	{
		using siv3dCreateNotificationCallback = void(*)(CToastNotification::Notification::IDType idx, void* userData);
		using siv3dNotificationEventCallback = void(*)(CToastNotification::Notification::IDType idx, ToastNotificationState state, void* userData);

		__attribute__((import_name("siv3dCreateNotification")))
		extern CToastNotification::Notification::IDType siv3dCreateNotification(const char* title, const char* body, size_t actionsNum, const char* const* actions, siv3dCreateNotificationCallback callback, void* userData);

		__attribute__((import_name("siv3dRegisterNotificationCallback")))
		extern void siv3dRegisterNotificationCallback(CToastNotification::Notification::IDType idx, siv3dNotificationEventCallback callback, void* userData);

		__attribute__((import_name("siv3dCloseNotification")))
		extern void siv3dCloseNotification(CToastNotification::Notification::IDType idx);

		__attribute__((import_name("siv3dQueryNotificationPermission")))
		extern CToastNotification::NotificationPermission siv3dQueryNotificationPermission();
	}

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
		return detail::siv3dQueryNotificationPermission() != NotificationPermission::Denied;
	}

	ToastNotificationID CToastNotification::show(const ToastNotificationItem& item)
	{
		const auto& title = item.title.toUTF8();
		const auto& message = item.message.toUTF8();

		const auto& actions = item.actions.map([](const auto& item) { return item.toUTF8(); });
		const auto& actionsCptr = actions.map([](const auto& item) { return item.c_str(); });

		return detail::siv3dCreateNotification(
			title.c_str(), message.c_str(), 
			actions.size(), actionsCptr.data(), 
			&CToastNotification::OnCreateNotification, this);
	}

	ToastNotificationState CToastNotification::getState(ToastNotificationID idx)
	{
		auto it = m_notifications.find(idx);

		if (it == m_notifications.end())
		{
			return(ToastNotificationState::None_);
		}

		return it->second.state;
	}

	Optional<size_t> CToastNotification::getAction(ToastNotificationID)
	{
		// [Siv3D ToDo]
		return(none);
	}

	void CToastNotification::hide(ToastNotificationID idx)
	{
		detail::siv3dCloseNotification(idx);
	}

	void CToastNotification::clear()
	{
		for (auto [ key, state ] : m_notifications)
		{
			detail::siv3dCloseNotification(key);
		}

		m_notifications.clear();
	}

	void CToastNotification::onStateUpdate(size_t idx, ToastNotificationState state, const Optional<int32>&)
	{
		auto it = m_notifications.find(idx);

		if (it == m_notifications.end())
		{
			return;
		}

		it->second.state = state;
	}

	void CToastNotification::OnStateUpdate(Notification::IDType idx, ToastNotificationState state, void* userData)
	{
		auto& notification = *static_cast<CToastNotification*>(userData);

		notification.onStateUpdate(static_cast<size_t>(idx), state, none);
	}

	void CToastNotification::OnCreateNotification(Notification::IDType idx, void* userData)
	{
		auto& notification = *static_cast<CToastNotification*>(userData);

		notification.m_notifications[idx] = Notification{};

		detail::siv3dRegisterNotificationCallback(idx, &CToastNotification::OnStateUpdate, &notification);
	}
}
