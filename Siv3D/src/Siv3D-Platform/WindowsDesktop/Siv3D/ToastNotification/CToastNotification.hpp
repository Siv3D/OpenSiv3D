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
# include <Siv3D/HashTable.hpp>
# include <Siv3D/ToastNotification/IToastNotification.hpp>

namespace s3d
{
	struct ToastState
	{
		ToastNotificationID id = -1;

		ToastNotificationState state = ToastNotificationState::None_;

		Optional<size_t> action;
	};

	class CToastNotification final : public ISiv3DToastNotification
	{
	public:

		CToastNotification();

		~CToastNotification() override;

		void init() override;

		bool isAvailable() const override;

		ToastNotificationID show(const ToastNotificationItem& item) override;

		ToastNotificationState getState(ToastNotificationID id) override;

		Optional<size_t> getAction(ToastNotificationID id) override;

		void hide(ToastNotificationID id) override;

		void clear() override;

		void onStateUpdate(size_t index, ToastNotificationState state, const Optional<int32>& option) override;

	private:

		mutable Optional<bool> m_available2;

		Optional<bool> m_initialized;

		HashTable<ToastNotificationID, size_t> m_toastIDTable;

		HashTable<size_t, ToastState> m_toasts;

		size_t m_indexCount = 0;

		std::mutex m_mutex;

		void checkAvailability() const;

		bool setup();
	};
}
