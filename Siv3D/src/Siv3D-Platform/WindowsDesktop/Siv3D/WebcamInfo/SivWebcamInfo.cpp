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

# include <Siv3D/WebcamInfo.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <dshow.h>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static bool CreateSystemDeviceEnum(ICreateDevEnum** systemDeviceEnum)
		{
			return SUCCEEDED(::CoCreateInstance(CLSID_SystemDeviceEnum, nullptr, CLSCTX_INPROC, IID_ICreateDevEnum,
				reinterpret_cast<void**>(systemDeviceEnum)));
		}
	}

	namespace System
	{
		Array<WebcamInfo> EnumerateWebcams()
		{
			Array<WebcamInfo> results;

			ComPtr<ICreateDevEnum> devEnum;

			if (not detail::CreateSystemDeviceEnum(&devEnum))
			{
				return results;
			}

			ComPtr<IEnumMoniker> enumMoniker;

			if (FAILED(devEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &enumMoniker, 0)))
			{
				return results;
			}

			if (not enumMoniker)
			{
				return results;
			}

			ComPtr<IMoniker> moniker;

			for (uint32 index = 0; enumMoniker->Next(1, &moniker, nullptr) == S_OK; ++index)
			{
				ComPtr<IPropertyBag> propertyBag;

				if (FAILED(moniker->BindToStorage(0, 0, IID_IPropertyBag, &propertyBag)))
				{
					continue;
				}

				VARIANT var;
				var.vt = VT_BSTR;

				if (FAILED(propertyBag->Read(L"FriendlyName", &var, 0)))
				{
					continue;
				}

				WebcamInfo info;
				info.name = Unicode::FromWstring(var.bstrVal);
				info.cameraIndex = index;

				VariantClear(&var);
				var.vt = VT_BSTR;

				if (SUCCEEDED(propertyBag->Read(L"DevicePath", &var, 0)))
				{
					info.uniqueName = Unicode::FromWstring(var.bstrVal);
				}

				results << info;
			}

			return results;
		}
	}
}
