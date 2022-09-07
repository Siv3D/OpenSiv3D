//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
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

namespace s3d
{
	namespace detail
	{
		static size_t WriteCallback(const char* ptr, const size_t size, const size_t nmemb, IWriter* pWriter)
		{
			const size_t size_bytes = (size * nmemb);

			pWriter->write(ptr, size_bytes);

			return size_bytes;
		}

		static size_t HeaderCallback(const char* buffer, const size_t size, const size_t nitems, std::string* userData)
		{
			const size_t size_bytes = (size * nitems);

			userData->append(buffer, size_bytes);

			return size_bytes;
		}
	}

	namespace SimpleHTTP
	{
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

			String temporaryFile{U"/tmp/file"};

			auto httpTask = SaveAsync(url, temporaryFile);
			auto httpFuture = Platform::Web::SimpleHTTP::CreateAsyncTask(httpTask);

			if (auto httpResponse = Platform::Web::System::WaitForFutureResolved(httpFuture))
			{
				BinaryReader temporaryFileReader{temporaryFile};

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

			return {};
		}

		AsyncHTTPTask SaveAsync(const URLView url, const FilePathView filePath)
		{
			SIV3D_ENGINE(Network)->init();

			return AsyncHTTPTask{ url, filePath };
		}
	}
}