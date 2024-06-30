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

# include <Siv3D/Dialog.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Wave.hpp>
# include <Siv3D/Audio.hpp>
# include <Siv3D/AudioDecoder.hpp>
# include <Siv3D/System.hpp>
# include <Siv3D/EngineLog.hpp>
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
		}

		Optional<FilePath> OpenFile(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView title)
		{		
			auto openFileFuture = Platform::Web::Dialog::OpenFile(filters);
			
			if (auto path = Platform::Web::System::AwaitAsyncTask(openFileFuture))
			{
				return *path;
			}
			else
			{
				LOG_ERROR(U"cannot use Dialog::OpenFile without Asyncify. Please confirm that linker option contains `-sASYNCIFY=1`");
				return (none);
			}
		}

		Array<FilePath> OpenFiles(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView title)
		{
			auto openFileFuture = Platform::Web::Dialog::OpenFiles(filters);
			
			if (auto path = Platform::Web::System::AwaitAsyncTask(openFileFuture))
			{
				return *path;
			}
			else
			{
				LOG_ERROR(U"cannot use Dialog::OpenFiles without Asyncify. Please confirm that linker option contains `-sASYNCIFY=1`");
				return {};
			}
		}

		Optional<FilePath> SaveFile(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView title, const StringView defaultFileName)
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
			using siv3dOpenDialogCallback = void (*)(char**, uint32, std::promise<T>*);

			template <class T>
			__attribute__((import_name("siv3dOpenDialogAsync")))
			void siv3dOpenDialogImpl(const char*, siv3dOpenDialogCallback<T>, std::promise<T>*, bool allowMultiple);

			template <class T>
			void OnOpenFileDialogClosed(char** fileNames, uint32 fileNamesCount, std::promise<T>* result)
			{
				if (fileNames == 0)
				{
					result->set_value(T{});
				}
				else
				{
					auto path = Unicode::Widen(fileNames[0]);
					result->set_value(T{path});
				}

				delete result;
			}

			template<>
			void OnOpenFileDialogClosed<Array<FilePath>>(char** fileNames, uint32 fileNamesCount, std::promise<Array<FilePath>>* result)
			{
				if (fileNames == 0)
				{
					result->set_value(Array<FilePath>{});
				}
				else
				{
					Array<FilePath> pathes;

					for (uint32 i = 0; i < fileNamesCount; i++)
					{
						pathes << Unicode::Widen(fileNames[i]);
					}

					result->set_value(std::move(pathes));
				}

				delete result;
			}

			void OnOpenWaveDialogClosed(char** fileNames, uint32 fileNamesCount, std::promise<Wave>* result)
			{
				if (fileNames == 0)
				{
					result->set_value(Wave{});
				}
				else
				{
					auto path = Unicode::Widen(fileNames[0]);
					Platform::Web::AudioDecoder::DecodeFromFile(path, std::move(*result));
				}

				delete result;
			}

			void OnOpenAudioDialogClosed(char** fileNames, uint32 fileNamesCount, std::promise<Audio>* result)
			{
				if (fileNames == 0)
				{
					result->set_value(Audio{});
				}
				else
				{
					auto path = Unicode::Widen(fileNames[0]);
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

				delete result;
			}

			template <class T>
			std::future<T> siv3dOpenDialogAsync(const Array<FileFilter>& filters, bool allowMultiple = false, siv3dOpenDialogCallback<T> callback = &OnOpenFileDialogClosed<T>)
			{
				const auto filter = s3d::Dialog::detail::TransformFileFilters(filters);

				auto result = new std::promise<T>();
				auto result_future = result->get_future();
				
				siv3dOpenDialogImpl<T>(filter.narrow().c_str(), callback, result, allowMultiple);
				
				return result_future;
			}
		}

		AsyncTask<Optional<FilePath>> OpenFile(const Array<FileFilter>& filters, FilePathView defaultPath, StringView)
		{
			return detail::siv3dOpenDialogAsync<Optional<FilePath>>(filters);
		}

		AsyncTask<Array<FilePath>> OpenFiles(const Array<FileFilter>& filters, FilePathView defaultPath, StringView)
		{
			return detail::siv3dOpenDialogAsync<Array<FilePath>>(filters, true);
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
			return detail::siv3dOpenDialogAsync<Wave>({ FileFilter::AllAudioFiles() }, false, &detail::OnOpenWaveDialogClosed);
		}

		AsyncTask<Audio> OpenAudio(FilePathView defaultPath, StringView title)
		{
			return detail::siv3dOpenDialogAsync<Audio>({ FileFilter::AllAudioFiles() }, false, &detail::OnOpenAudioDialogClosed);
		}
	}
}
