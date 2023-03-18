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
# include <Siv3D/MemoryWriter.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Network/INetwork.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

# define CURL_STATICLIB
# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/curl/curl.h>
# else
#	include <curl/curl.h>
# endif

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
			SIV3D_ENGINE(Network)->init();

			return Get(url, {}, filePath);
		}

		HTTPResponse Load(const URLView url, MemoryWriter& writer)
		{
			SIV3D_ENGINE(Network)->init();

			return Get(url, {}, writer);
		}

		HTTPResponse Load(const URLView url, IWriter& writer)
		{
			SIV3D_ENGINE(Network)->init();

			return Get(url, {}, writer);
		}

		HTTPResponse Get(const URLView url, const HashTable<String, String>& headers, const FilePathView filePath)
		{
			SIV3D_ENGINE(Network)->init();

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
			SIV3D_ENGINE(Network)->init();

			if (auto result = Get(url, headers, static_cast<IWriter&>(writer)))
			{
				return result;
			}

			writer.clear();
			return{};
		}

		HTTPResponse Get(const URLView url, const HashTable<String, String>& headers, IWriter& writer)
		{
			SIV3D_ENGINE(Network)->init();

			if (not writer.isOpen())
			{
				return{};
			}

			::CURL* curl = ::curl_easy_init();
			{
				if (not curl)
				{
					return{};
				}
			}

			// ヘッダの追加
			::curl_slist* header_slist = nullptr;
			{
				for (auto&& [key, value] : headers)
				{
					const std::string header = (key.toUTF8() + ": " + value.toUTF8());
					header_slist = ::curl_slist_append(header_slist, header.c_str());
				}
			}

			const std::string urlUTF8 = Unicode::ToUTF8(url);
			::curl_easy_setopt(curl, ::CURLOPT_URL, urlUTF8.c_str());
			::curl_easy_setopt(curl, ::CURLOPT_FOLLOWLOCATION, 1L);
			::curl_easy_setopt(curl, ::CURLOPT_HTTPHEADER, header_slist);
			::curl_easy_setopt(curl, ::CURLOPT_WRITEFUNCTION, detail::WriteCallback);
			::curl_easy_setopt(curl, ::CURLOPT_WRITEDATA, &writer);

			// レスポンスヘッダーの設定
			std::string responseHeaders;
			{
				::curl_easy_setopt(curl, ::CURLOPT_HEADERFUNCTION, detail::HeaderCallback);
				::curl_easy_setopt(curl, ::CURLOPT_HEADERDATA, &responseHeaders);
			}

			const ::CURLcode result = ::curl_easy_perform(curl);
			::curl_easy_cleanup(curl);
			::curl_slist_free_all(header_slist);

			if (result != ::CURLE_OK)
			{
				LOG_FAIL(U"curl failed (CURLcode: {})"_fmt(FromEnum(result)));
				return{};
			}

			return HTTPResponse{ responseHeaders };
		}

		HTTPResponse Post(const URLView url, const HashTable<String, String>& headers, const void* src, const size_t size, const FilePathView filePath)
		{
			SIV3D_ENGINE(Network)->init();

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
			SIV3D_ENGINE(Network)->init();

			if (auto result = Post(url, headers, src, size, static_cast<IWriter&>(writer)))
			{
				return result;
			}

			writer.clear();
			return{};
		}

		HTTPResponse Post(const URLView url, const HashTable<String, String>& headers, const void* src, const size_t size, IWriter& writer)
		{
			SIV3D_ENGINE(Network)->init();

			if (not writer.isOpen())
			{
				return{};
			}

			::CURL* curl = ::curl_easy_init();
			{
				if (not curl)
				{
					return{};
				}
			}

			// ヘッダの追加
			::curl_slist* header_slist = nullptr;
			{
				for (auto&& [key, value] : headers)
				{
					const std::string header = (key.toUTF8() + ": " + value.toUTF8());
					header_slist = ::curl_slist_append(header_slist, header.c_str());
				}
			}

			const std::string urlUTF8 = Unicode::ToUTF8(url);
			::curl_easy_setopt(curl, ::CURLOPT_URL, urlUTF8.c_str());
			::curl_easy_setopt(curl, ::CURLOPT_FOLLOWLOCATION, 1L);
			::curl_easy_setopt(curl, ::CURLOPT_HTTPHEADER, header_slist);
			::curl_easy_setopt(curl, ::CURLOPT_POST, 1L);
			::curl_easy_setopt(curl, ::CURLOPT_POSTFIELDS, const_cast<char*>(static_cast<const char*>(src)));
			::curl_easy_setopt(curl, ::CURLOPT_POSTFIELDSIZE, static_cast<long>(size));
			::curl_easy_setopt(curl, ::CURLOPT_WRITEFUNCTION, detail::WriteCallback);
			::curl_easy_setopt(curl, ::CURLOPT_WRITEDATA, &writer);

			// レスポンスヘッダーの設定
			std::string responseHeaders;
			{
				::curl_easy_setopt(curl, ::CURLOPT_HEADERFUNCTION, detail::HeaderCallback);
				::curl_easy_setopt(curl, ::CURLOPT_HEADERDATA, &responseHeaders);
			}

			const ::CURLcode result = ::curl_easy_perform(curl);
			::curl_easy_cleanup(curl);
			::curl_slist_free_all(header_slist);

			if (result != ::CURLE_OK)
			{
				LOG_FAIL(U"curl failed (CURLcode: {})"_fmt(FromEnum(result)));
				return{};
			}

			return HTTPResponse{ responseHeaders };
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
