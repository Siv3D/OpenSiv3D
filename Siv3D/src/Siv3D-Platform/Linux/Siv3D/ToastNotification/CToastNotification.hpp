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
# include <Siv3D/ToastNotification/IToastNotification.hpp>

namespace s3d
{
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

	};
}
