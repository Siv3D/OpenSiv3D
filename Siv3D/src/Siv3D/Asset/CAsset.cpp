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

# include "CAsset.hpp"
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		String GetAssetTypeName(AssetType)
		{
			// [Siv3D ToDo]
			return U"Texture";
		}
	}

	CAsset::CAsset()
	{

	}

	CAsset::~CAsset()
	{
		// wait for all
		for (auto& assetList : m_assetLists)
		{
			for (auto& asset : assetList)
			{
				asset.second->wait();
			}
		}
	}

	bool CAsset::init()
	{
	
		LOG_INFO(U"ℹ️ Asset initialized");

		return true;
	}

	void CAsset::update()
	{

	}

	bool CAsset::registerAsset(const AssetType assetType, const String& name, std::unique_ptr<IAsset>&& asset)
	{
		auto& assetList = m_assetLists[static_cast<size_t>(assetType)];

		if (assetList.find(name) != assetList.end())
		{
			LOG_FAIL(U"{}Asset: Asset Name \"{}\" is already reserved. Use another name"_fmt(detail::GetAssetTypeName(assetType), name));

			return false;
		}

		auto result = assetList.emplace(name, std::move(asset));

		LOG_DEBUG(U"{}Asset: Asset \"{}\" was registered"_fmt(detail::GetAssetTypeName(assetType), name));

		if (result.first.value()->getParameter().loadAsync)
		{
			result.first.value()->preloadAsync();

			return true;
		}
		else if (result.first.value()->getParameter().loadImmediately)
		{
			return result.first.value()->preload();
		}

		return true;
	}

	IAsset* CAsset::getAsset(const AssetType assetType, const String& name)
	{
		const auto& assetList = m_assetLists[static_cast<size_t>(assetType)];

		const auto it = assetList.find(name);

		if (it == assetList.end())
		{
			//LOG_FAIL_ONCE(L"登録されていない ", groupName, L" アセット \"", name, L"\" を取得しようとしました。");

			return nullptr;
		}

		IAsset* pAsset = it->second.get();

		if (!pAsset->isPreloaded())
		{
			pAsset->wait();

			if (!pAsset->preload())
			{
				return nullptr;
			}	
		}

		return pAsset;
	}

	bool CAsset::isReady(const AssetType assetType, const String& name)
	{
		const auto& assetList = m_assetLists[static_cast<size_t>(assetType)];

		const auto it = assetList.find(name);

		if (it == assetList.end())
		{
			//LOG_FAIL_ONCE(L"登録されていない ", groupName, L" アセット \"", name, L"\" を取得しようとしました。");

			return false;
		}

		return it->second->isReady();
	}
}
