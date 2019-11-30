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
# include <Siv3D/ToastNotification.hpp>
# include <ToastNotification/IToastNotification.hpp>

namespace s3d
{
	class CToastNotification : public ISiv3DToastNotification
	{
	private:

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
