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
# include <Siv3D/HashTable.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Logger.hpp>
# include "../Siv3DEngine.hpp"
# include "../Profiler/IProfiler.hpp"

namespace s3d
{
	template <class IDType, class Data>
	class AssetHandleManager
	{
	private:

		const IDType NullID = IDType(0);

		using MapType = HashTable<IDType, std::shared_ptr<Data>>;

		MapType m_data;

		String m_assetTypeName;

		typename IDType::ValueType m_idCount = 0;

		bool m_idFilled = false;

		std::mutex m_mutex;

	public:

		using iterator			= typename MapType::iterator;
		using const_iterator	= typename MapType::const_iterator;

		explicit AssetHandleManager(const String& name)
			: m_assetTypeName(name) {}

		void setNullData(const std::shared_ptr<Data>& data)
		{
			m_data.emplace(NullID, data);

			LOG_DEBUG(U"💠 Created {0}[0(null)]"_fmt(m_assetTypeName));
		}

		Data* operator [](const IDType id)
		{
			return m_data[id].get();
		}

		IDType add(const std::shared_ptr<Data>& data)
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			if (++m_idCount == 0)
			{
				m_idFilled = true;
			}

			if (!m_idFilled)
			{
				m_data.emplace(m_idCount, data);

				LOG_DEBUG(U"💠 Created {0}[{1}]"_fmt(m_assetTypeName, m_idCount));

				return IDType(m_idCount);
			}

			if (m_data.size() == m_data.max_size())
			{
				LOG_FAIL(U"❌ No more {0}s can be created"_fmt(m_assetTypeName));

				return NullID;
			}

			for (;;)
			{
				if (m_data.find(IDType(++m_idCount)) == m_data.end())
				{
					m_data.emplace(m_idCount, data);

					LOG_DEBUG(U"💠 Created {0}[{1}]"_fmt(m_assetTypeName, m_idCount));

					return IDType(m_idCount);
				}
			}
		}

		void erase(const IDType id)
		{
			if (id.isNullAsset())
			{
				return;
			}

			std::lock_guard<std::mutex> lock(m_mutex);

			const auto it = m_data.find(id);

			assert(it != m_data.end());

			LOG_DEBUG(U"♻️ Released {0}[{1}]"_fmt(m_assetTypeName, id.value()));

			m_data.erase(it);

			ASSET_RELEASE();
		}

		void destroy()
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			for (const auto& data : m_data)
			{
				if (const auto id = data.first; !id.isNullAsset())
				{
					LOG_DEBUG(U"♻️ Released {0}[{1}]"_fmt(m_assetTypeName, id.value()));
				}
				else
				{
					LOG_DEBUG(U"♻️ Released {0}[0(null)]"_fmt(m_assetTypeName));
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
