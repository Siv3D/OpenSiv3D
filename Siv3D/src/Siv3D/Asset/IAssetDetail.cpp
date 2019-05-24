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

# include <functional>
# include "IAssetDetail.hpp"

namespace s3d
{
	IAsset::IAssetDetail::IAssetDetail()
	{

	}

	IAsset::IAssetDetail::IAssetDetail(const AssetParameter& parameter)
		: m_parameter(parameter)
	{

	}

	IAsset::IAssetDetail::~IAssetDetail()
	{

	}

	void IAsset::IAssetDetail::setState(const State state)
	{
		m_state = state;
	}

	const AssetParameter& IAsset::IAssetDetail::getParameter() const
	{
		return m_parameter;
	}

	bool IAsset::IAssetDetail::isReady() const
	{
		if (!m_loadingThread)
		{
			return true;
		}

		return m_loadingThread->is_done();
	}

	void IAsset::IAssetDetail::wait()
	{
		if (m_state != State::PreloadingAsync)
		{
			return;
		}

		m_state = m_loadingThread->get() ? State::LoadSucceeded : State::LoadFailed;

		m_loadingThread.reset();
	}

	bool IAsset::IAssetDetail::isLoadingAsync()
	{
		if (m_state != State::PreloadingAsync)
		{
			return false;
		}

		if (isReady())
		{
			m_state = m_loadingThread->get() ? State::LoadSucceeded : State::LoadFailed;

			m_loadingThread.reset();
		}

		return false;
	}

	bool IAsset::IAssetDetail::isPreloaded() const
	{
		return (m_state == State::LoadSucceeded || m_state == State::LoadFailed);
	}

	bool IAsset::IAssetDetail::loadSucceeded() const
	{
		return (m_state == State::LoadSucceeded);
	}

	bool IAsset::IAssetDetail::uninitialized() const
	{
		return (m_state == State::Uninitialized);
	}

	void IAsset::IAssetDetail::launchLoading(std::function<bool()>&& loader)
	{
		m_loadingThread = std::make_unique<ConcurrentTask<bool>>(CreateConcurrentTask(std::move(loader)));
	}
}
