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

# include "CAsset.hpp"
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		constexpr StringView GetAssetTypeName(const AssetType assetType) noexcept
		{
			switch (assetType)
			{
			case AssetType::Audio:
				return U"Audio"_sv;
			case AssetType::Texture:
				return U"Texture"_sv;
			case AssetType::Font:
				return U"Font"_sv;
			case AssetType::VertexShader:
				return U"VertexShader"_sv;
			case AssetType::PixelShader:
				return U"PixelShader"_sv;
			default:
				return U"Unknown"_sv;
			}
		}
	}

	CAsset::CAsset() {}

	CAsset::~CAsset()
	{
		LOG_SCOPED_TRACE(U"CAsset::~CAsset()");

		SIV3D_ENGINE(Texture)->updateAsyncTextureLoad(Largest<size_t>);

		// wait for all
		for (auto& assetList : m_assetLists)
		{
			for (auto& asset : assetList)
			{
				asset.second->wait();
			}
		}
	}

	void CAsset::update()
	{
		SIV3D_ENGINE(Texture)->updateAsyncTextureLoad(4);
	}

	bool CAsset::registerAsset(const AssetType assetType, const AssetNameView name, std::unique_ptr<IAsset>&& asset)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];

		if (assetList.contains(name))
		{
			LOG_FAIL(U"❌ {}Asset: Asset Name `{}` is already reserved. Use another name"_fmt(detail::GetAssetTypeName(assetType), name));
			return false;
		}

		assetList.emplace(name, std::move(asset));

		LOG_TRACE(U"ℹ️ {}Asset: Asset `{}` registered"_fmt(detail::GetAssetTypeName(assetType), name));

		return true;
	}

	IAsset* CAsset::getAsset(const AssetType assetType, const AssetNameView name)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];
		const auto it = assetList.find(name);

		if (it == assetList.end())
		{
			//LOG_FAIL_ONCE(U"❌ CAsset::getAsset(): Unregistered {}Asset `{}`"_fmt(detail::GetAssetTypeName(assetType), name));
			return nullptr;
		}

		IAsset* pAsset = it->second.get();

		if (not pAsset->isFinished())
		{
			if (pAsset->isAsyncLoading())
			{
				return nullptr;
			}

			if (not pAsset->load())
			{
				return nullptr;
			}
		}

		return pAsset;
	}

	bool CAsset::isRegistered(const AssetType assetType, const AssetNameView name) const
	{
		return m_assetLists[FromEnum(assetType)].contains(name);
	}

	bool CAsset::load(const AssetType assetType, const AssetNameView name, const StringView hint)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];
		const auto it = assetList.find(name);

		if (it == assetList.end())
		{
			//LOG_FAIL_ONCE(U"❌ CAsset::load(): Unregistered {}Asset: `{}`"_fmt(detail::GetAssetTypeName(assetType), name));
			return false;
		}

		return it->second->load(String{ hint });
	}

	void CAsset::loadAsync(const AssetType assetType, const AssetNameView name, const StringView hint)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];
		const auto it = assetList.find(name);

		if (it == assetList.end())
		{
			//LOG_FAIL_ONCE(U"❌ CAsset::loadAsync(): Unregistered {}Asset: `{}`"_fmt(detail::GetAssetTypeName(assetType), name));
			return;
		}

		it->second->loadAsync(String{ hint });
	}

	void CAsset::wait(const AssetType assetType, const AssetNameView name)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];
		const auto it = assetList.find(name);

		if (it == assetList.end())
		{
			//LOG_FAIL_ONCE(U"❌ CAsset::wait(): Unregistered {}Asset: `{}`"_fmt(detail::GetAssetTypeName(assetType), name));
			return;
		}

		it->second->wait();
	}

	bool CAsset::isReady(const AssetType assetType, const AssetNameView name)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];
		const auto it = assetList.find(name);

		if (it == assetList.end())
		{
			//LOG_FAIL_ONCE(U"❌ CAsset::isReady(): Unregistered {}Asset: `{}`"_fmt(detail::GetAssetTypeName(assetType), name));
			return false;
		}

		return it->second->isFinished();
	}

	void CAsset::release(const AssetType assetType, const AssetNameView name)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];
		const auto it = assetList.find(name);

		if (it == assetList.end())
		{
			//LOG_FAIL_ONCE(U"❌ CAsset::release(): Unregistered {}Asset: `{}`"_fmt(detail::GetAssetTypeName(assetType), name));
			return;
		}

		it->second->release();

		LOG_TRACE(U"ℹ️ {}Asset: `{}` released"_fmt(detail::GetAssetTypeName(assetType), name));
	}

	void CAsset::releaseAll(const AssetType assetType)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];

		for (auto&&[name, asset] : assetList)
		{
			asset->release();

			LOG_TRACE(U"ℹ️ {}Asset: `{}` released"_fmt(detail::GetAssetTypeName(assetType), name));
		}
	}

	void CAsset::unregister(const AssetType assetType, const AssetNameView name)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];
		const auto it = assetList.find(name);

		if (it == assetList.end())
		{
			//LOG_FAIL_ONCE(U"❌ CAsset::unregister(): Unregistered {}Asset: `{}`"_fmt(detail::GetAssetTypeName(assetType), name));
			return;
		}

		it->second->release();

		assetList.erase(it);

		LOG_TRACE(U"ℹ️ {}Asset: `{}` unregistered"_fmt(detail::GetAssetTypeName(assetType), name));
	}

	void CAsset::unregisterAll(const AssetType assetType)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];

		for (auto&& [name, asset] : assetList)
		{
			asset->release();

			LOG_TRACE(U"ℹ️ {}Asset: `{}` unregistered"_fmt(detail::GetAssetTypeName(assetType), name));
		}

		assetList.clear();
	}

	HashTable<AssetName, AssetInfo> CAsset::enumerate(const AssetType assetType)
	{
		HashTable<AssetName, AssetInfo> result;

		auto& assetList = m_assetLists[FromEnum(assetType)];

		result.reserve(assetList.size());

		for (auto&& [name, asset] : assetList)
		{
			result.emplace(name, AssetInfo{ asset->getState(), asset->getTags() });
		}

		return result;
	}
}
