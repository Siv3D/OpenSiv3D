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

# include "ZIPReaderDetail.hpp"
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/EngineLog.hpp>
# include <ThirdParty/minizip/mz.h>
# include <ThirdParty/minizip/mz_strm.h>
# include <ThirdParty/minizip/mz_strm_mem.h>
# include <ThirdParty/minizip/mz_zip.h>
# include <ThirdParty/minizip/mz_zip_rw.h>

namespace s3d
{
	namespace detail
	{
		struct ZipOption
		{
			bool allowOverwrite = true;
		};

		static int32 ExtractEntryCallback(void*, void*, [[maybe_unused]] mz_zip_file* file_info, const char*)
		{
			LOG_TRACE(U"Extracting: `{}`"_fmt(Unicode::Widen(file_info->filename)));

			return MZ_OK;
		}

		static int32 ExtractProgressCallback(void* handle, void*, mz_zip_file* file_info, int64_t position)
		{
			uint8 raw = 0;
			::mz_zip_reader_get_raw(handle, &raw);

			[[maybe_unused]] double progress = 0;

			if (raw && file_info->compressed_size > 0)
			{
				progress = (static_cast<double>(position) / file_info->compressed_size) * 100;
			}
			else if (!raw && file_info->uncompressed_size > 0)
			{
				progress = (static_cast<double>(position) / file_info->uncompressed_size) * 100;
			}

			LOG_TRACE(U"Extracting: {:.1f}%"_fmt(progress));

			return MZ_OK;
		}

		static int32 ExtractOverwriteCallback(void*, void* zipOption, mz_zip_file*, [[maybe_unused]] const char* path)
		{
			const ZipOption* option = static_cast<ZipOption*>(zipOption);

			if (!option->allowOverwrite)
			{
				LOG_TRACE(U"Extracting: path `{}` already exists"_fmt(Unicode::Widen(path)));

				return MZ_EXIST_ERROR;
			}

			return MZ_OK;
		}
	}

	ZIPReader::ZIPReaderDetail::ZIPReaderDetail()
	{
		// do nothing
	}

	ZIPReader::ZIPReaderDetail::~ZIPReaderDetail()
	{
		close();
	}

	bool ZIPReader::ZIPReaderDetail::open(const FilePathView path)
	{
		if (isOpen())
		{
			close();
		}

		::mz_zip_reader_create(&m_reader);

		detail::ZipOption option;
		::mz_zip_reader_set_entry_cb(m_reader, &option, detail::ExtractEntryCallback);
		::mz_zip_reader_set_progress_cb(m_reader, &option, detail::ExtractProgressCallback);
		::mz_zip_reader_set_overwrite_cb(m_reader, &option, detail::ExtractOverwriteCallback);

		{
			int32 err = MZ_OK;
			
		# if SIV3D_PLATFORM(WINDOWS)

			if (FileSystem::IsResource(path))
			{
				m_resource = ZIPResourceHolder(path);

				err = ::mz_zip_reader_open_buffer(m_reader,
					const_cast<uint8*>(static_cast<const std::uint8_t*>(m_resource.data())),
					static_cast<int32>(m_resource.size()), 0);
			}
			else
			{
				const std::string archivePathC = Unicode::Narrow(path);
				err = ::mz_zip_reader_open_file(m_reader, archivePathC.c_str());
			}

		# else

			const std::string archivePathC = Unicode::Narrow(path);
			err = ::mz_zip_reader_open_file(m_reader, archivePathC.c_str());

		# endif

			if (err != MZ_OK)
			{
				close();
				return false;
			}

			err = ::mz_zip_reader_goto_first_entry(m_reader);

			if ((err != MZ_OK) && (err != MZ_END_OF_LIST))
			{
				close();
				return{};
			}

			do
			{
				mz_zip_file* fileInfo = nullptr;
				err = ::mz_zip_reader_entry_get_info(m_reader, &fileInfo);

				if (err != MZ_OK)
				{
					break;
				}

				m_paths << Unicode::Widen(fileInfo->filename);

				err = ::mz_zip_reader_goto_next_entry(m_reader);

				if ((err != MZ_OK) && (err != MZ_END_OF_LIST))
				{
					break;
				}
			} while (err == MZ_OK);

			if (err != MZ_END_OF_LIST)
			{
				close();
				return false;
			}
		}

		m_archiveFileFullPath = FileSystem::FullPath(path);

		return true;
	}

	void ZIPReader::ZIPReaderDetail::close()
	{
		if (not isOpen())
		{
			return;
		}

		m_paths.clear();

		m_archiveFileFullPath.clear();

		::mz_zip_reader_delete(&m_reader); // 内部で m_reader = nullptr;
	}

	bool ZIPReader::ZIPReaderDetail::isOpen() const noexcept
	{
		return (m_reader != nullptr);
	}

	const Array<FilePath>& ZIPReader::ZIPReaderDetail::enumPaths() const
	{
		return m_paths;
	}

	bool ZIPReader::ZIPReaderDetail::extractAll(const FilePathView targetDirectory) const
	{
		return extract(StringView(), targetDirectory);
	}

	bool ZIPReader::ZIPReaderDetail::extract(const StringView pattern, const FilePathView targetDirectory) const
	{
		if (not isOpen())
		{
			return false;
		}

		if ((not targetDirectory.ends_with(U'/')) && (not FileSystem::IsDirectory(targetDirectory)))
		{
			LOG_FAIL(U"ZIPReader::extract(): `{}` is not a directory"_fmt(targetDirectory));
			return false;
		}

		int32 err = MZ_OK;

		if (pattern)
		{
			const std::string patternC = Unicode::Narrow(pattern);
			::mz_zip_reader_set_pattern(m_reader, patternC.c_str(), 1);
		}
		else
		{
			::mz_zip_reader_set_pattern(m_reader, "*", 1);
		}

		const std::string targetDirectoryC = Unicode::Narrow(targetDirectory);
		err = ::mz_zip_reader_save_all(m_reader, targetDirectoryC.c_str());

		if (err == MZ_END_OF_LIST)
		{
			if (pattern)
			{
				LOG_FAIL(U"ZIPReader::extract(): Files matching `{}` not found in archive"_fmt(pattern));
			}
			else
			{
				LOG_TRACE(U"ZIPReader::extract(): No files in archive");
				err = MZ_OK;
			}
		}
		else if (err != MZ_OK)
		{
			LOG_FAIL(U"ZIPReader::extract(): Failed to save entries");
		}

		return (err == MZ_OK);
	}

	Blob ZIPReader::ZIPReaderDetail::extractToBlob(const FilePathView filePath) const
	{
		if (not isOpen())
		{
			return{};
		}

		const std::string patternC = Unicode::Narrow(filePath);
		Array<Byte> data;
		int32 err = MZ_OK;

		::mz_zip_reader_set_pattern(m_reader, patternC.c_str(), 1);

		err = ::mz_zip_reader_goto_first_entry(m_reader);

		if (err == MZ_END_OF_LIST)
		{
			LOG_FAIL(U"ZIPReader::extractToMemory(): Files matching `{}` not found in archive"_fmt(filePath));
			return{};
		}

		if (err != MZ_OK)
		{
			LOG_FAIL(U"ZIPReader::extractToMemory(): Failed to find an entry");
			return{};
		}

		const int32 bufferLength = ::mz_zip_reader_entry_save_buffer_length(m_reader);

		if (bufferLength < 0)
		{
			LOG_FAIL(U"ZIPReader::extractToMemory(): Failed to get buffer length");
			return{};
		}

		data.resize(static_cast<size_t>(bufferLength));

		err = ::mz_zip_reader_entry_save_buffer(m_reader, static_cast<void*>(data.data()), bufferLength);

		if (err != MZ_OK)
		{
			LOG_FAIL(U"ZIPReader::extractToMemory(): Failed to save buffer");
			return{};
		}

		return Blob{ std::move(data) };
	}
}
