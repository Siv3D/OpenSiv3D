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

# include <atomic>
# include <thread>
# include <unordered_set>

# include <gio/gio.h>

namespace s3d
{
	class CToastNotification : public ISiv3DToastNotification
	{
	private:
		bool m_available = false;

		Array<String> m_serverCapabilities;
		bool m_markupSupported = false;
		bool m_actionsSupported = false;

		std::unordered_set<guint32> notificationIDs;

		//Signalを受信するために接続を維持する必要がある
		GDBusConnection *conn = nullptr;
		GDBusProxy *proxy = nullptr;

		String m_serverName;
		String m_serverVendor;
		String m_serverVersion;
		String m_serverSpecVersion;

		std::atomic<bool> m_breakIteration = false;
		std::thread m_contextIterator;

		void ContextIteration();

		static void signalHandler(GDBusProxy *proxy, gchar *sender_name, gchar *signal_name, GVariant *params, gpointer user_data);

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

		bool supportsActions() const;
	};
}
