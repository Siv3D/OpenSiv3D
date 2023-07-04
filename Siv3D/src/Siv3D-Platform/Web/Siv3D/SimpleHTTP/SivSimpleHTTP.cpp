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
# include <Siv3D/SimpleHTTP.hpp>
# include <Siv3D/BinaryWriter.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/MemoryWriter.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Network/INetwork.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/AsyncHTTPTask.hpp>
# include <Siv3D/System.hpp>
# include "../AsyncHTTPTask/AsyncHTTPTaskDetail.hpp"

namespace s3d
{
	namespace SimpleHTTP
	{
		namespace detail
		{
			void CopyFileToIWriter(const StringView path, IWriter& writer)
			{
				BinaryReader temporaryFileReader{path};

				Array<uint8> buffer;
				buffer.resize(4096);

				while (true)
				{
					auto size = temporaryFileReader.read(buffer.data(), buffer.size());

					if (size == 0)
					{
						break;
					}

					writer.write(buffer.data(), size);
				}
			}

			__attribute__((import_name("siv3dLocateFile")))
			char* siv3dLocateFile();
		}

		HTTPResponse Save(const URLView url, const FilePathView filePath)
		{
			return Get(url, {}, filePath);
		}

		HTTPResponse Load(const URLView url, MemoryWriter& writer)
		{
			return Get(url, {}, writer);
		}

		HTTPResponse Load(const URLView url, IWriter& writer)
		{
			return Get(url, {}, writer);
		}

		HTTPResponse Get(const URLView url, const HashTable<String, String>& headers, const FilePathView filePath)
		{
			BinaryWriter writer{ filePath };
			{
				if (not writer)
				{
					return{};
				}
			}

			if (auto result = Get(url, headers, static_cast<IWriter&>(writer)))
			{
				return result;
			}

			writer.close();
			FileSystem::Remove(filePath);
			return{};
		}

		HTTPResponse Get(const URLView url, const HashTable<String, String>& headers, MemoryWriter& writer)
		{
			if (auto result = Get(url, headers, static_cast<IWriter&>(writer)))
			{
				return result;
			}

			writer.clear();
			return{};
		}

		HTTPResponse Get(const URLView url, const HashTable<String, String>& headers, IWriter& writer)
		{
			if (not writer.isOpen())
			{
				return{};
			}

			String origin{U""};

			const bool isWebPage = url.starts_with(U"http://")
				|| url.starts_with(U"https://");
			auto originNamePtr = detail::siv3dLocateFile();

			if (not isWebPage && originNamePtr)
			{
				origin = Unicode::FromUTF8(originNamePtr);
			}

			String temporaryFile{U"/tmp/file"};

			auto httpTask = std::make_unique<AsyncHTTPTaskDetail>(U"GET", origin + url, HashTable<String, String>{}, temporaryFile);

			for (auto&& [key, value] : headers)
			{
				httpTask->setRequestHeader(key, value);
			}

			httpTask->send(none);
			
			auto httpFuture = httpTask->CreateAsyncTask();

			if (auto httpResponse = Platform::Web::System::AwaitAsyncTask(httpFuture))
			{
				if (FileSystem::Exists(temporaryFile))
				{
					detail::CopyFileToIWriter(temporaryFile, writer);
					FileSystem::Remove(temporaryFile);
				}
				else
				{
					LOG_FAIL(U"❌ SimpleHttp: Failed to get the url `{0}`"_fmt(url));
				}

				return *httpResponse;
			}
			else
			{
				LOG_ERROR(U"cannot use SimpleHttp without Asyncify. Please confirm that linker option contains `-sASYNCIFY=1`");
				return {};
			}
		}

		HTTPResponse Post(const URLView url, const HashTable<String, String>& headers, const void* src, const size_t size, const FilePathView filePath)
		{
			BinaryWriter writer{ filePath };
			{
				if (not writer)
				{
					return{};
				}
			}

			if (auto result = Post(url, headers, src, size, static_cast<IWriter&>(writer)))
			{
				return result;
			}

			writer.close();
			FileSystem::Remove(filePath);
			return{};
		}

		HTTPResponse Post(const URLView url, const HashTable<String, String>& headers, const void* src, const size_t size, MemoryWriter& writer)
		{
			if (auto result = Post(url, headers, src, size, static_cast<IWriter&>(writer)))
			{
				return result;
			}

			writer.clear();
			return{};
		}

		HTTPResponse Post(const URLView url, const HashTable<String, String>& headers, const void* src, const size_t size, IWriter& writer)
		{
			if (not writer.isOpen())
			{
				return{};
			}

			String origin{U""};

			const bool isWebPage = url.starts_with(U"http://")
				|| url.starts_with(U"https://");
			auto originNamePtr = detail::siv3dLocateFile();

			if (not isWebPage && originNamePtr)
			{
				origin = Unicode::FromUTF8(originNamePtr);
			}

			String temporaryFile{U"/tmp/file"};

			auto httpTask = std::make_unique<AsyncHTTPTaskDetail>(U"POST", origin + url, HashTable<String, String>{}, temporaryFile);

			for (auto&& [key, value] : headers)
			{
				httpTask->setRequestHeader(key, value);
			}

			httpTask->send(std::string_view(static_cast<const char*>(src), size));
			
			auto httpFuture = httpTask->CreateAsyncTask();

			if (auto httpResponse = Platform::Web::System::AwaitAsyncTask(httpFuture))
			{
				if (FileSystem::Exists(temporaryFile))
				{
					detail::CopyFileToIWriter(temporaryFile, writer);
					FileSystem::Remove(temporaryFile);
				}
				else
				{
					LOG_FAIL(U"❌ SimpleHttp: Failed to post the url `{0}`"_fmt(url));
				}

				return *httpResponse;
			}
			else
			{
				LOG_ERROR(U"cannot use SimpleHttp without Asyncify. Please confirm that linker option contains `-sASYNCIFY=1`");
				return {};
			}
		}

		AsyncHTTPTask SaveAsync(const URLView url, const FilePathView filePath)
		{
			return GetAsync(url, {}, filePath);
		}

		AsyncHTTPTask LoadAsync(const URLView url)
		{
			return GetAsync(url, {});
		}

		AsyncHTTPTask GetAsync(const URLView url, const HashTable<String, String>& headers, const FilePathView filePath)
		{
			SIV3D_ENGINE(Network)->init();

			return AsyncHTTPTask{ url, headers, filePath };
		}

		AsyncHTTPTask GetAsync(const URLView url, const HashTable<String, String>& headers)
		{
			SIV3D_ENGINE(Network)->init();

			return AsyncHTTPTask{ url, headers };
		}

		AsyncHTTPTask PostAsync(const URLView url, const HashTable<String, String>& headers, const void* src, const size_t size, const FilePathView filePath)
		{
			SIV3D_ENGINE(Network)->init();

			return AsyncHTTPTask{ url, headers, src, size, filePath };
		}

		AsyncHTTPTask PostAsync(const URLView url, const HashTable<String, String>& headers, const void* src, const size_t size)
		{
			SIV3D_ENGINE(Network)->init();

			return AsyncHTTPTask{ url, headers, src, size };
		}
	}
}