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

# include <Siv3D/Common.hpp>
# include <Siv3D/AsyncHTTPTask.hpp>
# include "AsyncHTTPTaskDetail.hpp"

namespace s3d
{
	AsyncHTTPTask::AsyncHTTPTask()
		: pImpl{ std::make_shared<AsyncHTTPTaskDetail>() } 
	{}

	bool AsyncHTTPTask::isEmpty() const
	{
		return pImpl->isEmpty();
	}

	AsyncHTTPTask::operator bool() const
	{
		return (not isEmpty());
	}

	bool AsyncHTTPTask::isReady() const
	{
		return pImpl->isReady();
	}

	void AsyncHTTPTask::cancel()
	{
		pImpl->cancel();
	}

	HTTPAsyncStatus AsyncHTTPTask::getStatus() const
	{
		return pImpl->getStatus();
	}

	HTTPProgress AsyncHTTPTask::getProgress() const
	{
		return pImpl->getProgress();
	}

	bool AsyncHTTPTask::isDownloading() const
	{
		return (pImpl->getStatus() == HTTPAsyncStatus::Downloading);
	}

	bool AsyncHTTPTask::isFailed() const
	{
		return (pImpl->getStatus() == HTTPAsyncStatus::Failed);
	}

	bool AsyncHTTPTask::isCanceled() const
	{
		return (pImpl->getStatus() == HTTPAsyncStatus::Canceled);
	}

	bool AsyncHTTPTask::isSucceeded() const
	{
		return (pImpl->getStatus() == HTTPAsyncStatus::Succeeded);
	}

	const HTTPResponse& AsyncHTTPTask::getResponse()
	{
		return pImpl->getResponse();
	}

	AsyncHTTPTask::AsyncHTTPTask(const URLView url, const HashTable<String, String>& headers, const FilePathView path)
		: pImpl{ std::make_shared<AsyncHTTPTaskDetail>(url, headers, path) } 
	{
		pImpl->send(none);
	}

	namespace Platform::Web::SimpleHTTP
	{
		AsyncTask<HTTPResponse> CreateAsyncTask(AsyncHTTPTask& httpTask)
		{
			return httpTask.pImpl->CreateAsyncTask();
		}
	}
}