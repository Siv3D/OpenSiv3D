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

# include "CAddon.hpp"

namespace s3d
{
	bool CAddon::add(const StringView name, std::unique_ptr<IAddon>&& addon, const int32 priority)
	{
		if (isRegistered(name))
		{
			return false;
		}

		m_addons.emplace_back(std::move(addon), name, priority);
		m_addons.sort_by([](const AddonData& a, const AddonData& b) { return (a.priority > b.priority); });

		return true;
	}

	void CAddon::remove(const StringView name)
	{
		for (auto it = m_addons.begin(); it != m_addons.end(); ++it)
		{
			if (it->name == name)
			{
				m_addons.erase(it);
				return;
			}
		}
	}

	void CAddon::removeAll()
	{
		m_addons.clear();
	}

	bool CAddon::isRegistered(const StringView name) const noexcept
	{
		return m_addons.contains_if([=](const AddonData& a) { return (a.name == name); });
	}

	IAddon* CAddon::get(const StringView name)
	{
		for (auto it = m_addons.begin(); it != m_addons.end(); ++it)
		{
			if (it->name == name)
			{
				return it->pAddon.get();
			}
		}

		return nullptr;
	}

	bool CAddon::update()
	{
		for (auto& addon : m_addons)
		{
			if (not addon.pAddon->update())
			{
				return false;
			}
		}

		return true;
	}

	void CAddon::draw() const
	{
		for (const auto& addon : m_addons)
		{
			addon.pAddon->draw();
		}
	}

	void CAddon::postPresent()
	{
		for (auto& addon : m_addons)
		{
			addon.pAddon->postPresent();
		}
	}
}
