//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/EngineLog.hpp>
# include "CAsset.hpp"

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
	}

	void CAsset::update()
	{
		// [Siv3D ToDo]
	}

	bool CAsset::registerAsset(const AssetType assetType, const AssetName& name, std::unique_ptr<IAsset>&& asset)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];

		if (assetList.contains(name))
		{
			LOG_FAIL(U"❌ {}Asset: Asset Name \"{}\" is already reserved. Use another name"_fmt(detail::GetAssetTypeName(assetType), name));
			return false;
		}

		auto it = assetList.emplace(name, std::move(asset));

		LOG_TRACE(U"ℹ️ {}Asset: Asset \"{}\" registered"_fmt(detail::GetAssetTypeName(assetType), name));

		//if (result.first.value()->getParameter().loadAsync)
		//{
		//	result.first.value()->preloadAsync();

		//	return true;
		//}
		//else if (result.first.value()->getParameter().loadImmediately)
		//{
		//	return result.first.value()->preload();
		//}

		return true;
	}

	IAsset* CAsset::getAsset(const AssetType assetType, const AssetNameView name)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];
		const auto it = assetList.find(name);

		if (it == assetList.end())
		{
			//LOG_FAIL_ONCE(U"❌ CAsset::getAsset(): Unregistered {}Asset \"{}\""_fmt(detail::GetAssetTypeName(assetType), name));
			return nullptr;
		}

		IAsset* pAsset = it->second.get();

		if (not pAsset->isFinished())
		{
		//	if (pAsset->isLoadingAsync())
		//	{
		//		return nullptr;
		//	}

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

	void CAsset::release(const AssetType assetType, const AssetNameView name)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];
		const auto it = assetList.find(name);

		if (it == assetList.end())
		{
			//LOG_FAIL_ONCE(U"❌ CAsset::release(): Unregistered {}Asset: \"{}\""_fmt(detail::GetAssetTypeName(assetType), name));
			return;
		}

		IAsset* pAsset = it->second.get();

		//pAsset->wait();

		pAsset->release();

		LOG_TRACE(U"ℹ️ {}Asset: \"{}\" released"_fmt(detail::GetAssetTypeName(assetType), name));
	}

	void CAsset::releaseAll(const AssetType assetType)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];

		for (auto&&[name, asset] : assetList)
		{
			//asset.second->wait();

			asset->release();

			LOG_TRACE(U"ℹ️ {}Asset: \"{}\" released"_fmt(detail::GetAssetTypeName(assetType), name));
		}
	}

	void CAsset::unregister(const AssetType assetType, const AssetNameView name)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];
		const auto it = assetList.find(name);

		if (it == assetList.end())
		{
			//LOG_FAIL_ONCE(U"❌ CAsset::unregister(): Unregistered {}Asset: \"{}\""_fmt(detail::GetAssetTypeName(assetType), name));
			return;
		}

		IAsset* pAsset = it->second.get();

		//pAsset->wait();

		pAsset->release();

		assetList.erase(it);

		LOG_TRACE(U"ℹ️ {}Asset: \"{}\" unregistered"_fmt(detail::GetAssetTypeName(assetType), name));
	}

	void CAsset::unregisterAll(const AssetType assetType)
	{
		auto& assetList = m_assetLists[FromEnum(assetType)];

		for (auto&& [name, asset] : assetList)
		{
			//asset.second->wait();

			asset->release();

			LOG_TRACE(U"ℹ️ {}Asset: \"{}\" unregistered"_fmt(detail::GetAssetTypeName(assetType), name));
		}

		assetList.clear();
	}

	HashTable<AssetName, AssetState> CAsset::enumerate(const AssetType assetType)
	{
		HashTable<AssetName, AssetState> result;

		auto& assetList = m_assetLists[FromEnum(assetType)];

		result.reserve(assetList.size());

		for (auto&& [name, asset] : assetList)
		{
			result.emplace(name, asset->getState());
		}

		return result;
	}
}
