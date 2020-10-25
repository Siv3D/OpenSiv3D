// infoware - C++ System information Library
//
// Written in 2016-2020 by nabijaczleweli <nabijaczleweli@gmail.com> and ThePhD <phdofthehouse@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related
// and neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along with this software.
// If not, see <http://creativecommons.org/publicdomain/zero/1.0/>


#ifdef _WIN32


#include "infoware/detail/memory.hpp"
#include "infoware/detail/scope.hpp"
#include "infoware/detail/winstring.hpp"
#include "infoware/system.hpp"
#include <memory>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <wbemidl.h>
#include <windows.h>
//
//template <class Callback>
//class ScopeGuard final
//{
//private:
//
//	Callback m_callback;
//
//public:
//
//	ScopeGuard() = delete;
//
//	ScopeGuard(const ScopeGuard&) = delete;
//
//	ScopeGuard(Callback&& callback)
//		: m_callback(callback)
//	{
//	
//	}
//
//	~ScopeGuard()
//	{
//		m_callback();
//	}
//};

// Use WIM to acquire Win32_OperatingSystem.Name
// https://msdn.microsoft.com/en-us/library/aa390423(v=vs.85).aspx
static std::string version_name() {
	return std::string();
	//auto err = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	//if(FAILED(err) && err != RPC_E_CHANGED_MODE)
	//	return {};
	//ScopeGuard com_uninitialiser{ std::function<void()>(CoUninitialize) };

	//const auto init_result =
	//    CoInitializeSecurity(nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr);
	//if(FAILED(init_result) && init_result != RPC_E_TOO_LATE)
	//	return {};

	//IWbemLocator* wbem_loc_raw;
	//if(FAILED(CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, reinterpret_cast<void**>(&wbem_loc_raw))))
	//	return {};
	//std::unique_ptr<IWbemLocator, iware::detail::release_deleter> wbem_loc(wbem_loc_raw);

	//IWbemServices* wbem_services_raw;
	//wchar_t network_resource[] = LR"(ROOT\CIMV2)";
	//if(FAILED(wbem_loc->ConnectServer(network_resource, nullptr, nullptr, 0, 0, 0, 0, &wbem_services_raw)))
	//	return {};
	//std::unique_ptr<IWbemServices, iware::detail::release_deleter> wbem_services(wbem_services_raw);

	//if(FAILED(CoSetProxyBlanket(wbem_services.get(), RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr,
	//                            EOAC_NONE)))
	//	return {};

	//IEnumWbemClassObject* query_iterator_raw;
	//wchar_t query_lang[] = L"WQL";
	//wchar_t query[]      = L"SELECT Name FROM Win32_OperatingSystem";
	//if(FAILED(wbem_services->ExecQuery(query_lang, query, WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, nullptr, &query_iterator_raw)))
	//	return {};
	//std::unique_ptr<IEnumWbemClassObject, iware::detail::release_deleter> query_iterator(query_iterator_raw);

	//std::string ret;
	//while(query_iterator) {
	//	IWbemClassObject* value_raw;
	//	unsigned long iter_result;

	//	query_iterator->Next(static_cast<LONG>(WBEM_INFINITE), 1, &value_raw, &iter_result);
	//	if(!iter_result)
	//		break;
	//	std::unique_ptr<IWbemClassObject, iware::detail::release_deleter> value(value_raw);

	//	VARIANT val;
	//	value->Get(L"Name", 0, &val, 0, 0);
	//	ScopeGuard val_destructor{[&] { VariantClear(&val); }};

	//	ret = iware::detail::narrowen_bstring(val.bstrVal);
	//}
	//return ret.substr(0, ret.find('|'));
}


iware::system::OS_info_t iware::system::OS_info() {
	const auto kernel_version = iware::system::kernel_info();
	return {"Windows NT", version_name(), kernel_version.major, kernel_version.minor, kernel_version.patch, kernel_version.build_number};
}


#endif
