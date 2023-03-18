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

# include <Siv3D/AudioDecoder.hpp>
# include <Siv3D/BinaryReader.hpp>
# include "IAudioDecoder.hpp"
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Browser.hpp>

namespace s3d
{
	namespace AudioDecoder
	{
		AudioFormat GetAudioFormat(const FilePathView path)
		{
			BinaryReader reader{ path };

			if (not reader)
			{
				return AudioFormat::Unknown;
			}

			return SIV3D_ENGINE(AudioDecoder)->getAudioFormat(reader);
		}

		AudioFormat GetAudioFormat(IReader& reader)
		{
			return SIV3D_ENGINE(AudioDecoder)->getAudioFormat(reader);
		}

		Wave Decode(const FilePathView path, const AudioFormat audioFormat)
		{
			BinaryReader reader{ path };

			if (not reader)
			{
				return{};
			}

			return SIV3D_ENGINE(AudioDecoder)->decode(reader, path, audioFormat);
		}

		Wave Decode(const FilePathView path, const StringView decoderName)
		{
		# if SIV3D_PLATFORM(WEB)
			Platform::Web::FetchFile(path);
		# endif

			BinaryReader reader{ path };

			if (not reader)
			{
				return{};
			}

			return SIV3D_ENGINE(AudioDecoder)->decode(reader, decoderName);
		}

		Wave Decode(IReader& reader, const AudioFormat audioFormat)
		{
			return SIV3D_ENGINE(AudioDecoder)->decode(reader, {}, audioFormat);
		}

		Wave Decode(IReader& reader, const StringView decoderName)
		{
			return SIV3D_ENGINE(AudioDecoder)->decode(reader, decoderName);
		}

		bool Add(std::unique_ptr<IAudioDecoder>&& decoder)
		{
			return SIV3D_ENGINE(AudioDecoder)->add(std::move(decoder));
		}

		void Remove(const StringView name)
		{
			return SIV3D_ENGINE(AudioDecoder)->remove(name);
		}

		const Array<std::unique_ptr<IAudioDecoder>>& Enum()
		{
			return SIV3D_ENGINE(AudioDecoder)->enumDecoder();
		}
	}
}
