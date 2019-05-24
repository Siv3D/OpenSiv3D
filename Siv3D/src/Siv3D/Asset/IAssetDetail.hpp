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

# pragma once
# define SIV3D_CONCURRENT
# include <Siv3D/ConcurrentTask.hpp>
# include <Siv3D/Asset.hpp>

namespace s3d
{
	class IAsset::IAssetDetail
	{
	private:

		AssetParameter m_parameter;

		std::unique_ptr<ConcurrentTask<bool>> m_loadingThread;

		State m_state = State::Uninitialized;

	public:

		IAssetDetail();

		IAssetDetail(const AssetParameter& parameter);

		~IAssetDetail();

		void setState(const State state);

		const AssetParameter& getParameter() const;

		bool isReady() const;

		void wait();

		bool isLoadingAsync();

		bool isPreloaded() const;

		bool loadSucceeded() const;

		bool uninitialized() const;

		void launchLoading(std::function<bool()>&& loader);
	};
}
