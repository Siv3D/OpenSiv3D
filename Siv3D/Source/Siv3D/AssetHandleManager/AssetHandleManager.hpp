//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <memory>
# include <Siv3D/HashMap.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	template <class IDType, class Data>
	class AssetHandleManager
	{
	private:

		using MapType = HashMap<IDType, Data>;

		enum : IDType { NullID = 0 };

		String m_assetTypeName;

		IDType m_idCount = IDType(0);

		bool m_idFilled = false;

		MapType m_data;

	public:

		using iterator			= typename MapType::iterator;
		using const_iterator	= typename MapType::const_iterator;

		explicit AssetHandleManager(const String& name)
			: m_assetTypeName(name) {}

		void setNullData(const Data& data)
		{
			m_data.emplace(NullID, data);

			LOG_DEBUG(L"💠 Created {0}[0(null)]"_fmt(m_assetTypeName));
		}

		const Data& operator [](const IDType id)
		{
			return m_data[id];
		}

		IDType add(const Data& data)
		{
			if (++m_idCount == NullID)
			{
				m_idFilled = true;
			}

			if (!m_idFilled)
			{
				m_data.emplace(m_idCount, data);

				LOG_DEBUG(L"💠 Created {0}[{1}]"_fmt(m_assetTypeName, m_idCount));

				return m_idCount;
			}

			if (m_data.size() == m_data.max_size())
			{
				LOG_FAIL(L"❌ No more {0}s can be created"_fmt(m_assetTypeName));

				return NullID;
			}

			for (;;)
			{
				if (m_data.find(++m_idCount) == m_data.end())
				{
					m_data.emplace(m_idCount, data);

					LOG_DEBUG(L"💠 Created {0}[{1}]"_fmt(m_assetTypeName, m_idCount));

					return m_idCount;
				}
			}
		}

		void erase(const IDType id)
		{
			if (id == NullID)
			{
				return;
			}

			const auto it = m_data.find(id);

			assert(it != m_data.end());

			LOG_DEBUG(L"♻️ Released {0}[{1}]"_fmt(m_assetTypeName, id));

			m_data.erase(it);
		}

		void destroy()
		{
			for (const auto& data : m_data)
			{
				if (const auto id = data.first)
				{
					LOG_DEBUG(L"♻️ Released {0}[{1}]"_fmt(m_assetTypeName, id));
				}
				else
				{
					LOG_DEBUG(L"♻️ Released {0}[0(null)]"_fmt(m_assetTypeName));
				}
			}

			m_data.clear();
		}

		iterator begin()
		{
			return m_data.begin();
		}

		iterator end()
		{
			return m_data.end();
		}

		const_iterator begin() const
		{
			return m_data.cbegin();
		}

		const_iterator end() const
		{
			return m_data.cend();
		}
	};
}
