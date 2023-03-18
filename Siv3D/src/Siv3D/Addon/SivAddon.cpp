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

# include <Siv3D/Addon.hpp>
# include <Siv3D/Addon/IAddon.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Addon
	{
		bool Register(const StringView name, std::unique_ptr<IAddon>&& pAddon, const int32 priority)
		{
			return SIV3D_ENGINE(Addon)->add(name, std::move(pAddon), priority, priority);
		}

		bool Register(const StringView name, std::unique_ptr<IAddon>&& pAddon, const int32 updatePriority, const int32 drawPriority)
		{
			return SIV3D_ENGINE(Addon)->add(name, std::move(pAddon), updatePriority, drawPriority);
		}

		void Unregister(const StringView name)
		{
			SIV3D_ENGINE(Addon)->remove(name);
		}

		void UnregisterAll()
		{
			SIV3D_ENGINE(Addon)->removeAll();
		}

		bool IsRegistered(const StringView name)
		{
			return SIV3D_ENGINE(Addon)->isRegistered(name);
		}

		IAddon* GetIAddon(const StringView name)
		{
			return SIV3D_ENGINE(Addon)->get(name);
		}
	}
}
