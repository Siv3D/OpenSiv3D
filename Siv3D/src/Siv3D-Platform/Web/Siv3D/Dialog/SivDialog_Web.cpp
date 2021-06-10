//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Dialog.hpp>
# include <Siv3D/FileSystem.hpp>
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
			__attribute__((import_name("siv3dSaveDialog")))
			extern void siv3dSaveDialog(const char* fileName);
		}

		Optional<FilePath> OpenFile(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView title)
		{
			// [Siv3D ToDo]
			return (none);
		}

		Array<FilePath> OpenFiles(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView title)
		{
			// [Siv3D ToDo]
			return{};
		}

		Optional<FilePath> SaveFile(const Array<FileFilter>& filters, const FilePathView defaultPath, const StringView title)
		{
			const auto fileName = FileSystem::FileName(defaultPath);
			detail::siv3dSaveDialog(fileName.narrow().c_str());
			
			return FilePath(U"/dev/save");
		}

		Optional<FilePath> SelectFolder(const FilePathView defaultPath, const StringView title)
		{
			// [Siv3D ToDo]
			return (none);
		}
	}

	namespace Platform::Web::Dialog
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

			template <class T>
			using siv3dOpenDialogCallback = void (*)(char*, std::promise<T>*);

			template <class T>
			__attribute__((import_name("siv3dOpenDialog")))
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

						[](std::promise<Audio>& promise, std::future<Wave>& future) 
						{
							if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
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
			std::future<T> siv3dOpenDialog(const Array<FileFilter>& filters, siv3dOpenDialogCallback<T> callback = &OnOpenFileDialogClosed<T>)
			{
				const auto filter = TransformFileFilters(filters);

				auto result = new std::promise<T>();
				auto result_future = result->get_future();
				
				siv3dOpenDialogImpl<T>(filter.narrow().c_str(), callback, result);
				
				return result_future;
			}
		}

		std::future<Optional<FilePath>> OpenFile(const Array<FileFilter>& filters, FilePathView defaultPath, StringView)
		{
			return detail::siv3dOpenDialog<Optional<FilePath>>(filters);
		}



		std::future<Image> OpenImage(FilePathView defaultPath, StringView title)
		{
			return detail::siv3dOpenDialog<Image>({ FileFilter::AllImageFiles() });
		}

		std::future<Texture> OpenTexture(FilePathView defaultPath, StringView title)
		{
			return detail::siv3dOpenDialog<Texture>({ FileFilter::AllImageFiles() });
		}

		std::future<Texture> OpenTexture(const TextureDesc desc, FilePathView defaultPath, StringView title)
		{
			return detail::siv3dOpenDialog<Texture>({ FileFilter::AllImageFiles() });
		}

		std::future<Wave> OpenWave(FilePathView defaultPath, StringView title)
		{
			return detail::siv3dOpenDialog<Wave>({ FileFilter::AllAudioFiles() }, &detail::OnOpenWaveDialogClosed);
		}

		std::future<Audio> OpenAudio(FilePathView defaultPath, StringView title)
		{
			return detail::siv3dOpenDialog<Audio>({ FileFilter::AllAudioFiles() }, &detail::OnOpenAudioDialogClosed);
		}
	}
}
