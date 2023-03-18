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

# pragma once
# include <memory>
# include <mutex>
# include <Siv3D/Common.hpp>
# include <Siv3D/HashTable.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	template <class IDType, class Data>
	class AssetHandleManager
	{
	private:

		using MapType = HashTable<IDType, std::unique_ptr<Data>>;

		MapType m_data;

		String m_assetTypeName;

		typename IDType::value_type m_idCount = 0;

		bool m_idFilled = false;

		std::mutex m_mutex;

	public:

		using iterator = typename MapType::iterator;
		using const_iterator = typename MapType::const_iterator;

		explicit AssetHandleManager(const String& name)
			: m_assetTypeName{ name } {}

		void setNullData(std::unique_ptr<Data>&& data)
		{
			m_data.emplace(IDType::NullAsset(), std::move(data));

			LOG_TRACE(U"💠 Created {0}[0(null)]"_fmt(m_assetTypeName));
		}

		[[nodiscard]]
		Data* operator [](const IDType id)
		{
			std::lock_guard lock{ m_mutex };

			return m_data[id].get();
		}

		[[nodiscard]]
		IDType add(std::unique_ptr<Data>&& data, [[maybe_unused]] const String& info = U"")
		{
			std::lock_guard lock{ m_mutex };

			if (++m_idCount == IDType::InvalidID)
			{
				m_idFilled = true;
				m_idCount = 0;
			}

			if (not m_idFilled)
			{
				m_data.emplace(m_idCount, std::move(data));

				LOG_TRACE(U"💠 Created {0}[{1}] {2}"_fmt(m_assetTypeName, m_idCount, info));

				return IDType(m_idCount);
			}
			else
			{
				if (m_data.size() == (IDType::InvalidID - 1))
				{
					LOG_FAIL(U"❌ No more {0}s can be created"_fmt(m_assetTypeName));

					return IDType::NullAsset();
				}

				while (++m_idCount < IDType::InvalidID)
				{
					if (m_data.find(IDType(++m_idCount)) == m_data.end())
					{
						m_data.emplace(m_idCount, std::move(data));

						LOG_TRACE(U"💠 Created {0}[{1}] {2}"_fmt(m_assetTypeName, m_idCount, info));

						return IDType(m_idCount);
					}
				}

				return IDType::NullAsset();
			}
		}

		void erase(const IDType id)
		{
			if (id.isNull())
			{
				return;
			}

			std::lock_guard lock{ m_mutex };

			const auto it = m_data.find(id);

			assert(it != m_data.end());

			LOG_TRACE(U"♻️ Released {0}[{1}]"_fmt(m_assetTypeName, id.value()));

			m_data.erase(it);

			SIV3D_ENGINE(AssetMonitor)->released();
		}

		void destroy()
		{
			std::lock_guard lock{ m_mutex };

			for (const auto& data : m_data)
			{
				if (const auto id = data.first; !id.isNull())
				{
					LOG_TRACE(U"♻️ Released {0}[{1}]"_fmt(m_assetTypeName, id.value()));
				}
				else
				{
					LOG_TRACE(U"♻️ Released {0}[0(null)]"_fmt(m_assetTypeName));
				}
			}

			m_data.clear();
		}

		[[nodiscard]]
		iterator begin()
		{
			return m_data.begin();
		}

		[[nodiscard]]
		iterator end()
		{
			return m_data.end();
		}

		[[nodiscard]]
		const_iterator begin() const
		{
			return m_data.cbegin();
		}

		[[nodiscard]]
		const_iterator end() const
		{
			return m_data.cend();
		}

		[[nodiscard]]
		size_t size() const noexcept
		{
			return m_data.size();
		}
	};
}

