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

# include <Siv3D/Dialog.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/Audio.hpp>
# include <Siv3D/AudioDecoder.hpp>
# include <Siv3D/PseudoThread/PseudoThread.hpp>

namespace s3d
{
	namespace Dialog
	{
		namespace detail
		{
			String TransformFileFilters(const Array<FileFilter>& filters) 
			{
				return filters
					.map([](const FileFilter& f) 
					{
						return f.patterns
							.map([](const String& p) 
							{
								return p.count(U'/') == 1 ? p : U"." + p;
							})
							.join(U",", U"", U"");
					})
					.join(U",", U"", U"");
			}

			__attribute__((import_name("siv3dOpenDialog")))
			char* siv3dOpenDialogImpl(const char*);
		}

		Optional<FilePath> OpenFile(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView title)
		{
			const auto filter = detail::TransformFileFilters(filters);
			auto rawFilePath = detail::siv3dOpenDialogImpl(filter.narrow().c_str());

			if (rawFilePath == nullptr)
			{
				return (none);
			}
			else
			{
				auto filePath = Unicode::FromUTF8(rawFilePath);
				delete rawFilePath;
				return (filePath);
			}	
		}

		Array<FilePath> OpenFiles(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView title)
		{
			const auto filter = detail::TransformFileFilters(filters);
			auto rawFilePath = detail::siv3dOpenDialogImpl(filter.narrow().c_str());

			if (rawFilePath == nullptr)
			{
				return {};
			}
			else
			{
				auto filePath = Unicode::FromUTF8(rawFilePath);
				delete rawFilePath;
				return { filePath };
			}
		}

		Optional<FilePath> SaveFile(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView title)
		{
			// [Siv3D Web NoSupport]
			return (none);
		}

		Optional<FilePath> SelectFolder(const FilePathView defaultPath, const StringView title)
		{
			// [Siv3D Web NoSupport]
			return (none);
		}
	}

	namespace Platform::Web::Dialog
	{
		namespace detail
		{
			template <class T>
			using siv3dOpenDialogCallback = void (*)(char*, std::promise<T>*);

			template <class T>
			__attribute__((import_name("siv3dOpenDialogAsync")))
			void siv3dOpenDialogImpl(const char*, siv3dOpenDialogCallback<T>, std::promise<T>*);

			template <class T>
			void OnOpenFileDialogClosed(char* fileName, std::promise<T>* result)
			{
				if (fileName == 0)
				{
					result->set_value(T{});
				}
				else
				{
					auto path = Unicode::Widen(fileName);
					result->set_value(T{path});
				}

				delete fileName;
				delete result;
			}

			void OnOpenWaveDialogClosed(char* fileName, std::promise<Wave>* result)
			{
				if (fileName == 0)
				{
					result->set_value(Wave{});
				}
				else
				{
					auto path = Unicode::Widen(fileName);
					Platform::Web::AudioDecoder::DecodeFromFile(path, std::move(*result));
				}

				delete fileName;
				delete result;
			}

			void OnOpenAudioDialogClosed(char* fileName, std::promise<Audio>* result)
			{
				if (fileName == 0)
				{
					result->set_value(Audio{});
				}
				else
				{
					auto path = Unicode::Widen(fileName);
					auto waveFuture = Platform::Web::AudioDecoder::DecodeFromFile(path);

					PseudoThread futureResolver
					{ 
						std::chrono::milliseconds(30),

						[](std::promise<Audio>& promise, AsyncTask<Wave>& future) 
						{
							if (future.isReady())
							{
								promise.set_value(Audio { future.get() });
								return false;
							}

							return true;
						}, 

						std::move(*result), std::move(waveFuture) 
					};

					futureResolver.detach();
				}

				delete fileName;
				delete result;
			}

			template <class T>
			std::future<T> siv3dOpenDialogAsync(const Array<FileFilter>& filters, siv3dOpenDialogCallback<T> callback = &OnOpenFileDialogClosed<T>)
			{
				const auto filter = s3d::Dialog::detail::TransformFileFilters(filters);

				auto result = new std::promise<T>();
				auto result_future = result->get_future();
				
				siv3dOpenDialogImpl<T>(filter.narrow().c_str(), callback, result);
				
				return result_future;
			}
		}

		AsyncTask<Optional<FilePath>> OpenFile(const Array<FileFilter>& filters, FilePathView defaultPath, StringView)
		{
			return detail::siv3dOpenDialogAsync<Optional<FilePath>>(filters);
		}



		AsyncTask<Image> OpenImage(FilePathView defaultPath, StringView title)
		{
			return detail::siv3dOpenDialogAsync<Image>({ FileFilter::AllImageFiles() });
		}

		AsyncTask<Texture> OpenTexture(FilePathView defaultPath, StringView title)
		{
			return detail::siv3dOpenDialogAsync<Texture>({ FileFilter::AllImageFiles() });
		}

		AsyncTask<Texture> OpenTexture(const TextureDesc desc, FilePathView defaultPath, StringView title)
		{
			return detail::siv3dOpenDialogAsync<Texture>({ FileFilter::AllImageFiles() });
		}

		AsyncTask<Wave> OpenWave(FilePathView defaultPath, StringView title)
		{
			return detail::siv3dOpenDialogAsync<Wave>({ FileFilter::AllAudioFiles() }, &detail::OnOpenWaveDialogClosed);
		}

		AsyncTask<Audio> OpenAudio(FilePathView defaultPath, StringView title)
		{
			return detail::siv3dOpenDialogAsync<Audio>({ FileFilter::AllAudioFiles() }, &detail::OnOpenAudioDialogClosed);
		}
	}

	namespace Platform::Web
	{
		namespace detail
		{
			__attribute__((import_name("siv3dDownloadFile")))
			void siv3dDownloadFile(const char* filePath, const char* fileName, const char* mimeType = nullptr);
		}

		void DownloadFile(FilePathView filePath)
		{
			const auto fileName = FileSystem::FileName(filePath);
			detail::siv3dDownloadFile(filePath.narrow().c_str(), fileName.narrow().c_str());
		}
	}
}
