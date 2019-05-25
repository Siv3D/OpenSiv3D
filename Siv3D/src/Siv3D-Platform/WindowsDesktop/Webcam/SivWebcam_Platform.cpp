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

# include <Siv3D/Webcam.hpp>
# include <Siv3D/Windows.hpp>
# include <dshow.h>

namespace s3d
{
	namespace detail
	{
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

			if (!detail::CreateSystemDeviceEnum(&devEnum))
			{
				return results;
			}

			ComPtr<IEnumMoniker> enumMoniker;

			if (FAILED(devEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &enumMoniker, 0)))
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
				info.name	= Unicode::FromWString(var.bstrVal);
				info.index	= index;

				VariantClear(&var);
				var.vt = VT_BSTR;

				if (SUCCEEDED(propertyBag->Read(L"DevicePath", &var, 0)))
				{
					info.uniqueName = Unicode::FromWString(var.bstrVal);
				}

				results << info;
			}

			return results;
		}
	}
}
