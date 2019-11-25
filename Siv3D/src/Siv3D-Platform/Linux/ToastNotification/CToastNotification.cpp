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
# include <Siv3D/Window.hpp>
# include <Siv3D/FileSystem.hpp>
# include "CToastNotification.hpp"

#include <gio/gio.h>

namespace s3d
{
	namespace detail
	{
		const char *NAME_Notifications = "org.freedesktop.Notifications";
		const char *OBJECT_Notifications = "/org/freedesktop/Notifications";
		const char *INTERFACE_Notifications = "org.freedesktop.Notifications";

		void CloseDBusProxyAndConnection(GDBusProxy **proxy, GDBusConnection **conn)
		{
			if(!*proxy)
			{
				g_object_unref(*proxy);
			}

			if(!*conn)
			{
				g_object_unref(*conn);
			}
		}

		bool OpenDBusConnectionAndProxy(GDBusConnection **conn, GDBusProxy **proxy)
		{
			GError *error = nullptr;
			*conn = g_bus_get_sync(G_BUS_TYPE_SESSION, nullptr, &error);
			if(*conn == nullptr)
			{
				LOG_FAIL(U"❌ ToastNotification: g_bus_get_sync() failed. (message: {})"_fmt(Unicode::Widen(error->message)));
				return false;
			}

			*proxy = g_dbus_proxy_new_sync(*conn, G_DBUS_PROXY_FLAGS_NONE, nullptr,
					NAME_Notifications, OBJECT_Notifications, INTERFACE_Notifications, nullptr, &error);
			if(*proxy == nullptr)
			{
				detail::CloseDBusProxyAndConnection(proxy, conn);
				LOG_FAIL(U"❌ ToastNotification: g_dbus_proxy_new_sync() failed. (message: {})"_fmt(Unicode::Widen(error->message)));
				return false;
			}

			return true;
		}
	}

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

		GDBusConnection *conn = nullptr;;
		GDBusProxy *proxy = nullptr;;
		GError *error = nullptr;
		GVariant *ret;

		const char* METHOD_GetCapabilities = "GetCapabilities";
		const char* METHOD_GetServerInformation = "GetServerInformation";

		bool opened = detail::OpenDBusConnectionAndProxy(&conn, &proxy);
		if(!opened) return;

		// Get server information
		ret = g_dbus_proxy_call_sync(proxy, METHOD_GetServerInformation, g_variant_new("()"),
				G_DBUS_CALL_FLAGS_NONE, -1, nullptr, &error);
		if(ret == nullptr)
		{
			detail::CloseDBusProxyAndConnection(&proxy, &conn);
			LOG_FAIL(U"❌ ToastNotification: g_dbus_proxy_call_sync() failed. (method: {}, mesasge: {})."_fmt(Unicode::Widen(METHOD_GetServerInformation), Unicode::Widen(error->message)));
			g_error_free(error);
			return;
		}
		if(!g_variant_is_of_type(ret, G_VARIANT_TYPE("(ssss)")))
		{
			g_variant_unref(ret);
			detail::CloseDBusProxyAndConnection(&proxy, &conn);
			LOG_FAIL(U"❌ ToastNotification: g_variant_is_of_type() failed.");
			return;
		}
		for(gsize i = 0; i < 4; ++i)
		{
			gchar* str = nullptr;
			g_autoptr(GVariant) data = g_variant_get_child_value(ret, i);
			g_variant_get(data, "s", &str);

			if(i == 0) m_serverName = Unicode::Widen(str);
			else if(i == 1) m_serverVendor = Unicode::Widen(str);
			else if(i == 2) m_serverVersion = Unicode::Widen(str);
			else if(i == 3) m_serverSpecVersion = Unicode::Widen(str);

			g_free(str);
		}
		g_variant_unref(ret);
		LOG_INFO(U"ℹ️  ToastNotification: Notification server information: (Name: {}, Vendor: {}, Version: {}, SpecVersion: {})"_fmt(m_serverName, m_serverVendor, m_serverVersion, m_serverSpecVersion));


		// Get server capabilities
		ret = g_dbus_proxy_call_sync(proxy, METHOD_GetCapabilities, g_variant_new("()"),
				G_DBUS_CALL_FLAGS_NONE, -1, nullptr, &error);
		if(ret == nullptr)
		{
			detail::CloseDBusProxyAndConnection(&proxy, &conn);
			LOG_FAIL(U"❌ ToastNotification: g_dbus_proxy_call_sync() failed. (method: {}, mesasge: {})."_fmt(Unicode::Widen(METHOD_GetCapabilities), Unicode::Widen(error->message)));
			g_error_free(error);
			return;
		}
		if(!g_variant_is_of_type(ret, G_VARIANT_TYPE("(as)")))
		{
			g_variant_unref(ret);
			detail::CloseDBusProxyAndConnection(&proxy, &conn);
			LOG_FAIL(U"❌ ToastNotification: g_variant_is_of_type() failed.");
			return;
		}
		{
			GVariantIter *iter = nullptr;
			gchar *str = nullptr;
			g_variant_get(ret, "(as)", &iter);
			while(g_variant_iter_loop(iter, "s", &str))
			{
				m_serverCapabilities.push_back(Unicode::Widen(str));

				if(strncmp(str, "body-markup", strlen("body-markup")) == 0)
					m_markupSupported = true;
			}
		}
		g_variant_unref(ret);
		LOG_INFO(U"ℹ️  ToastNotification: Notification server capabilities: {}"_fmt(m_serverCapabilities));

		m_available = true;
		detail::CloseDBusProxyAndConnection(&proxy, &conn);

		LOG_INFO(U"ℹ️ CToastNotification initialized");
	}

	bool CToastNotification::isAvailable() const
	{
		return m_available;
	}

	NotificationID CToastNotification::show(const ToastNotificationProperty& prop)
	{
		const char* METHOD_Notify = "Notify";

		GDBusConnection *conn = nullptr;;
		GDBusProxy *proxy = nullptr;;
		bool opened = detail::OpenDBusConnectionAndProxy(&conn, &proxy);
		if(!opened) return -1;

		GVariantBuilder actions_builder;
		GVariantBuilder hints_builder;
		g_variant_builder_init(&actions_builder, G_VARIANT_TYPE("as"));
		g_variant_builder_init(&hints_builder, G_VARIANT_TYPE("a{sv}"));

		if(!prop.imagePath.empty())
		{
			FilePath image_fullpath = FileSystem::FullPath(prop.imagePath);
			g_variant_builder_add(&hints_builder, "{sv}",
				"image_path", g_variant_new_string(Unicode::Narrow(image_fullpath).c_str()));
		}

		String body;
		if(m_markupSupported)
			body = U"<b>" + prop.title + U"</b>\n\n" + prop.message;
		else
			body = prop.title + U"\n\n" + prop.message;

		GVariant *param = g_variant_new("(susssasa{sv}i)",
			Unicode::Narrow(Window::GetTitle()).c_str(),
			0,
			"",
			"",
			Unicode::Narrow(body).c_str(),
			&actions_builder,
			&hints_builder,
			-1
		);

		GError *error = nullptr;
		GVariant *ret = g_dbus_proxy_call_sync(proxy, METHOD_Notify, param, G_DBUS_CALL_FLAGS_NONE,
				-1, nullptr, &error);
		if(ret == nullptr)
		{
			detail::CloseDBusProxyAndConnection(&proxy, &conn);
			return(-1);
		}
		if(!g_variant_is_of_type(ret, G_VARIANT_TYPE("(u)")))
		{
			g_variant_unref(ret);
			detail::CloseDBusProxyAndConnection(&proxy, &conn);
			LOG_FAIL(U"❌ ToastNotification: g_variant_is_of_type() failed.");
			return -1;
		}

		guint32 id;
		g_variant_get(ret, "(u)", &id);

		g_variant_unref(ret);
		detail::CloseDBusProxyAndConnection(&proxy, &conn);

		return id;
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
