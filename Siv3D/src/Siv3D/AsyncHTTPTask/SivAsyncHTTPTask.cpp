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
# include <Siv3D/MemoryViewReader.hpp>
# include <Siv3D/JSON.hpp>
# include "AsyncHTTPTaskDetail.hpp"

namespace s3d
{
	AsyncHTTPTask::AsyncHTTPTask()
		: pImpl{ std::make_shared<AsyncHTTPTaskDetail>() } {}

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

	bool AsyncHTTPTask::isFile() const
	{
		return pImpl->isFile();
	}

	bool AsyncHTTPTask::isBlob() const
	{
		return (not pImpl->isFile());
	}

	const FilePath& AsyncHTTPTask::getFilePath() const
	{
		return pImpl->getFilePath();
	}

	const Blob& AsyncHTTPTask::getBlob() const
	{
		return pImpl->getBlob();
	}

	MemoryViewReader AsyncHTTPTask::getBlobReader() const
	{
		const Blob& blob = pImpl->getBlob();

		return{ blob.data(), blob.size_bytes() };
	}

	JSON AsyncHTTPTask::getAsJSON() const
	{
		if (pImpl->isFile())
		{
			return JSON::Load(getFilePath());
		}
		else
		{
			return JSON::Load(getBlobReader());
		}
	}

	AsyncHTTPTask::AsyncHTTPTask(const URLView url, const HashTable<String, String>& headers, const FilePathView path)
		: pImpl{ std::make_shared<AsyncHTTPTaskDetail>(url, headers, path) } {}

	AsyncHTTPTask::AsyncHTTPTask(const URLView url, const HashTable<String, String>& headers)
		: pImpl{ std::make_shared<AsyncHTTPTaskDetail>(url, headers) } {}

	AsyncHTTPTask::AsyncHTTPTask(const URLView url, const HashTable<String, String>& headers, const void* src, const size_t size, const FilePathView path)
		: pImpl{ std::make_shared<AsyncHTTPTaskDetail>(url, headers, src, size, path) } {}

	AsyncHTTPTask::AsyncHTTPTask(const URLView url, const HashTable<String, String>& headers, const void* src, const size_t size)
		: pImpl{ std::make_shared<AsyncHTTPTaskDetail>(url, headers, src, size) } {}
}