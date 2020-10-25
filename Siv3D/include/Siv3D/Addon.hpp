//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "IAddon.hpp"
# include "StringView.hpp"

namespace s3d
{
	namespace Addon
	{
		bool Register(StringView name, std::unique_ptr<IAddon>&& pAddon, int32 priority = 0);

		template <class AddonType, std::enable_if_t<std::is_base_of_v<IAddon, AddonType>>* = nullptr>
		bool Register(StringView name, int32 priority = 0);

		void Unregister(StringView name);

		void UnregisterAll();

		[[nodiscard]]
		bool IsRegistered(StringView name);

		[[nodiscard]]
		IAddon* GetIAddon(StringView name);

		template <class AddonType>
		[[nodiscard]]
		AddonType* GetAddon(StringView name);
	}
}

# include "detail/Addon.ipp"
