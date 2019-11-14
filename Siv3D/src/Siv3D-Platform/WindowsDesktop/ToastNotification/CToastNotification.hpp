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

# pragma once
# include <mutex>
# include <Siv3D/ToastNotification.hpp>
# include <Siv3D/HashTable.hpp>
# include <ToastNotification/IToastNotification.hpp>

namespace s3d
{
	struct ToastState
	{
		NotificationID id = -1;

		ToastNotificationState state = ToastNotificationState::None;

		Optional<size_t> action;
	};

	class CToastNotification : public ISiv3DToastNotification
	{
	private:

		bool m_available = false;

		Optional<bool> m_initialized;

		HashTable<NotificationID, size_t> m_toastIDTable;

		HashTable<size_t, ToastState> m_toasts;

		size_t m_indexCount = 0;

		std::mutex m_mutex;

		bool setup();

	public:

		CToastNotification();

		~CToastNotification() override;

		void init() override;

		bool isAvailable() const override;

		NotificationID show(const ToastNotificationProperty& prop) override;

		ToastNotificationState getState(NotificationID id) override;

		Optional<size_t> getAction(NotificationID id) override;

		void hide(NotificationID id) override;

		void clear() override;

		void onStateUpdate(size_t index, ToastNotificationState state, const Optional<int32>& option) override;
	};
}
