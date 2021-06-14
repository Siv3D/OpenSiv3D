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

# pragma once
# include <Siv3D/HashTable.hpp>
# include <Siv3D/String.hpp>
# include "IAsset.hpp"

namespace s3d
{
	class CAsset final : public ISiv3DAsset
	{
	public:

		CAsset();

		~CAsset() override;

		void update() override;

		bool registerAsset(AssetType assetType, const AssetName& name, std::unique_ptr<IAsset>&& asset) override;

		IAsset* getAsset(AssetType assetType, AssetNameView name) override;

		bool isRegistered(AssetType assetType, AssetNameView name) const override;

	private:

		std::array<HashTable<String, std::unique_ptr<IAsset>>, 5> m_assetLists;
	};
}
