//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Asset.hpp>
# include <Asset/IAssetDetail.hpp>

namespace s3d
{
	AssetParameter AssetParameter::Default()
	{
		return AssetParameter{};
	}

	AssetParameter AssetParameter::LoadImmediately()
	{
		AssetParameter parameter;

		parameter.loadImmediately = true;

		return parameter;
	}

	AssetParameter AssetParameter::LoadAsync()
	{
		AssetParameter parameter;

		parameter.loadImmediately = true;

		parameter.loadAsync = true;

		return parameter;
	}

	AssetParameter AssetParameter::withTag(const AssetTag& tag) const
	{
		AssetParameter parameter(*this);

		parameter.tags << tag;

		return parameter;
	}

	AssetParameter AssetParameter::withTag(const Array<AssetTag>& _tags) const
	{
		AssetParameter parameter(*this);

		parameter.tags.append(_tags);

		return parameter;
	}

	IAsset::IAsset()
		: pImpl(std::make_shared<IAssetDetail>())
	{

	}

	IAsset::IAsset(const AssetParameter& parameter)
		: pImpl(std::make_shared<IAssetDetail>(parameter))
	{

	}

	IAsset::~IAsset()
	{

	}

	const AssetParameter& IAsset::getParameter() const
	{
		return pImpl->getParameter();
	}

	bool IAsset::isReady() const
	{
		return pImpl->isReady();
	}

	void IAsset::wait()
	{
		pImpl->wait();
	}

	bool IAsset::isLoadingAsync()
	{
		return pImpl->isLoadingAsync();
	}

	bool IAsset::isPreloaded() const
	{
		return pImpl->isPreloaded();
	}

	bool IAsset::loadSucceeded() const
	{
		return pImpl->loadSucceeded();
	}

	void  IAsset::setState(const State state)
	{
		pImpl->setState(state);
	}

	bool IAsset::uninitialized() const
	{
		return pImpl->uninitialized();
	}

	void IAsset::launchLoading(std::function<bool()>&& loader)
	{
		pImpl->launchLoading(std::move(loader));
	}
}
