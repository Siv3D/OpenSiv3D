//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	namespace Addon
	{
		template <class AddonType, std::enable_if_t<std::is_base_of_v<IAddon, AddonType>>*>
		bool Register(const StringView name, const int32 priority)
		{
			if (IsRegistered(name))
			{
				return false;
			}

			std::unique_ptr<IAddon> pAddon = std::make_unique<AddonType>();

			if (not pAddon->init())
			{
				return false;
			}

			return Register(name, std::move(pAddon), priority);
		}

		template <class AddonType>
		AddonType* GetAddon(const StringView name)
		{
			return dynamic_cast<AddonType*>(GetIAddon(name));
		}
	}
}
