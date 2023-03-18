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

# include "CAddon.hpp"

namespace s3d
{
	namespace detail
	{
		static Array<std::pair<size_t, int32>> MakeUpdateIndices(const Array<AddonData>& addons)
		{
			Array<std::pair<size_t, int32>> indices(Arg::reserve = addons.size());

			size_t i = 0;

			for (const auto& addon : addons)
			{
				indices.emplace_back(i++, addon.updatePriority);
			}

			indices.sort_by([](const std::pair<size_t, int32>& a, const std::pair<size_t, int32>& b) { return (a.second > b.second); });

			return indices;
		}

		static Array<std::pair<size_t, int32>> MakeDrawIndices(const Array<AddonData>& addons)
		{
			Array<std::pair<size_t, int32>> indices(Arg::reserve = addons.size());

			size_t i = 0;

			for (const auto& addon : addons)
			{
				indices.emplace_back(i++, addon.drawPriority);
			}

			indices.sort_by([](const std::pair<size_t, int32>& a, const std::pair<size_t, int32>& b) { return (a.second > b.second); });

			return indices;
		}
	}

	AddonData::AddonData(std::unique_ptr<IAddon>&& _pAddon, StringView _name, int32 _updatePriority, int32 _drawPriority)
		: pAddon{ std::move(_pAddon) }
		, name{ _name }
		, updatePriority{ _updatePriority }
		, drawPriority{ _drawPriority } {}

	bool CAddon::add(const StringView name, std::unique_ptr<IAddon>&& addon, const int32 updatePriority, const int32 drawPriority)
	{
		if (isRegistered(name))
		{
			return false;
		}

		m_addons.emplace_back(std::move(addon), name, updatePriority, drawPriority);	
		m_updateIndices = detail::MakeUpdateIndices(m_addons);
		m_drawIndices = detail::MakeDrawIndices(m_addons);

		return true;
	}

	void CAddon::remove(const StringView name)
	{
		for (auto it = m_addons.begin(); it != m_addons.end(); ++it)
		{
			if (it->name == name)
			{
				m_addons.erase(it);
				m_updateIndices = detail::MakeUpdateIndices(m_addons);
				m_drawIndices = detail::MakeDrawIndices(m_addons);
				return;
			}
		}
	}

	void CAddon::removeAll()
	{
		m_addons.clear();
		m_updateIndices.clear();
		m_drawIndices.clear();
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
		for (const auto& index : m_updateIndices)
		{
			if (not m_addons[index.first].pAddon->update())
			{
				return false;
			}
		}

		return true;
	}

	void CAddon::draw() const
	{
		for (const auto& index : m_drawIndices)
		{
			m_addons[index.first].pAddon->draw();
		}
	}

	void CAddon::postPresent()
	{
		for (const auto& index : m_drawIndices)
		{
			m_addons[index.first].pAddon->postPresent();
		}
	}
}
