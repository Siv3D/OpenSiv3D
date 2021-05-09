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

# include <Siv3D/AudioFormat/OpusDecoder.hpp>
# include <Siv3D/EngineLog.hpp>

# if SIV3D_PLATFORM(WINDOWS) | SIV3D_PLATFORM(MACOS) | SIV3D_PLATFORM(WEB)
#	include <ThirdParty-prebuilt/ogg/ogg.h>
#	include <ThirdParty-prebuilt/opus/opus.h>
#	include <ThirdParty-prebuilt/opus/opus_multistream.h>
#	include <ThirdParty-prebuilt/opus/opusfile.h>
# else
#	include <ogg/ogg.h>
#	include <opus/opus.h>
#	include <opus/opus_multistream.h>
#	include <ThirdParty-prebuilt/opus/opusfile.h>
# endif

namespace s3d
{
	//StringView OpusDecoder::name() const
	//{
	//	return U"Opus"_sv;
	//}

	//bool OpusDecoder::isHeader(const uint8(&bytes)[48]) const
	//{
	//	static constexpr uint8 OGG_SIGN[] = { 0x4f, 0x67, 0x67 };
	//	//static constexpr uint8 VORBIS_SIGN[] = { 'v', 'o', 'r', 'v', 'i', 's' };
	//	static constexpr uint8 OPUS_SIGN[] = { 'O', 'p', 'u', 's' };
	//	const bool isOgg = (std::memcmp(bytes, OGG_SIGN, sizeof(OGG_SIGN)) == 0);

	//	if (!isOgg)
	//	{
	//		return false;
	//	}

	//	if (std::search(std::begin(bytes), std::end(bytes), std::begin(OPUS_SIGN), std::end(OPUS_SIGN))
	//		!= std::end(bytes))
	//	{
	//		return false;
	//	}

	//	return true;
	//}

	//const Array<String>& OpusDecoder::possibleExtensions() const
	//{
	//	static const Array<String> extensions = { U"ogg" };

	//	return extensions;
	//}

	//AudioFormat OpusDecoder::audioFormat() const noexcept
	//{
	//	return AudioFormat::Opus;
	//}

	//Wave OpusDecoder::decode(const FilePathView path) const
	//{
	//	return IAudioDecoder::decode(path);
	//}

	//Wave OpusDecoder::decode(IReader& reader, const FilePathView pathHint) const
	//{
	//	if (not reader.isOpen())
	//	{
	//		return{};
	//	}

	//	ov_callbacks callbacks;
	//	callbacks.read_func = detail::ReadOgg_Callback;
	//	callbacks.seek_func = detail::SeekOgg_Callback;
	//	callbacks.close_func = detail::CloseOgg_Callback;
	//	callbacks.tell_func = detail::TellOgg_Callback;

	//	Opus_File vf;

	//	if (::ov_open_callbacks(&reader, &vf, nullptr, -1, callbacks) != 0)
	//	{
	//		return{};
	//	}

	//	vorbis_info* vi = ::ov_info(&vf, -1);

	//	if (!vi)
	//	{
	//		::ov_clear(&vf);
	//		return{};
	//	}

	//	const uint32 samples = (::ov_pcm_total(&vf, -1)) & 0xffFFffFF;

	//	if (samples == 0)
	//	{
	//		return{};
	//	}

	//	const int32 channels = vi->channels;

	//	if (channels != 1 && channels != 2)
	//	{
	//		::ov_clear(&vf);
	//		return{};
	//	}

	//	Wave wave(samples, Arg::samplingRate = (vi->rate ? static_cast<uint32>(vi->rate) : Wave::DefaultSamplingRate));
	//	constexpr int32 BufferSize = 4096;
	//	std::array<char, BufferSize> buffer;
	//	WaveSample* pDst = wave.data();
	//	int current_sec = 0;

	//	if (channels == 1)
	//	{
	//		for (;;)
	//		{
	//			const long bytes_read = ::ov_read(&vf, buffer.data(), BufferSize, 0, 2, 1, &current_sec);
	//			const long samples_read = (bytes_read / 2);

	//			if (bytes_read == 0)
	//			{
	//				break;
	//			}
	//			else if (bytes_read < 0)
	//			{
	//				::ov_clear(&vf);
	//				return{};
	//			}

	//			const int16* pSrc = static_cast<const int16*>(static_cast<const void*>(buffer.data()));

	//			for (int32 i = 0; i < samples_read; ++i)
	//			{
	//				*pDst++ = WaveSampleS16(*pSrc++).asWaveSample();
	//			}
	//		}
	//	}
	//	else // channels == 2
	//	{
	//		for (;;)
	//		{
	//			const long bytes_read = ::ov_read(&vf, buffer.data(), BufferSize, 0, 2, 1, &current_sec);
	//			const long samples_read = (bytes_read / 4);

	//			if (bytes_read == 0)
	//			{
	//				break;
	//			}
	//			else if (bytes_read < 0)
	//			{
	//				::ov_clear(&vf);
	//				return{};
	//			}

	//			const int16* pSrc = static_cast<const int16*>(static_cast<const void*>(buffer.data()));

	//			for (int32 i = 0; i < samples_read; ++i)
	//			{
	//				const int16 left = *pSrc++;
	//				const int16 right = *pSrc++;
	//				*pDst++ = WaveSample::FromInt16(left, right);
	//			}
	//		}
	//	}

	//	::ov_clear(&vf);

	//	return wave;
	//}
}
