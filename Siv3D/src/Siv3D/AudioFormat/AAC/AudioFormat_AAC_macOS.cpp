//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS)

# include "AudioFormat_AAC_macOS.hpp"
# include "../../Siv3DEngine.hpp"
# include "../../Codec/ICodec.hpp"
# include "../../EngineUtility.hpp"
# include <AudioToolBox/AudioFile.h>
# include <AudioToolBox/AudioConverter.h>
# include <AudioToolbox/ExtendedAudioFile.h>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Logger.hpp>

namespace s3d
{
	namespace detail
	{
		class AACDecoder
		{
		private:
			
			ExtAudioFileRef m_audioFile = nullptr;
			
			AudioStreamBasicDescription m_inputFormat = {};
			
			AudioStreamBasicDescription m_outputFormat = {};

			size_t m_frameLength = 0;

			int32 read(const size_t size, WaveSample* pDst)
			{
				const uint32 outputChannels = m_outputFormat.mChannelsPerFrame;
				uint32 totalFramesToRead = static_cast<uint32>(size / m_inputFormat.mChannelsPerFrame);
				uint32 framesRead = 0;

				while (framesRead < totalFramesToRead)
				{
					const uint32 framesToRead = totalFramesToRead - framesRead;
					uint32 numFrames = framesToRead;
					
					AudioBufferList bufferList;
					bufferList.mNumberBuffers = 1;
					bufferList.mBuffers[0].mNumberChannels = outputChannels;
					bufferList.mBuffers[0].mDataByteSize = framesToRead * outputChannels * sizeof(float);
					bufferList.mBuffers[0].mData = pDst + framesRead;

					if (ExtAudioFileRead(m_audioFile, &numFrames, &bufferList) != noErr)
					{
						return 0;
					}
					
					if (!numFrames)
					{
						break;
					}
					
					framesRead += numFrames;
				}
				
				return framesRead * m_outputFormat.mChannelsPerFrame;
			}
			
		public:
			
			~AACDecoder()
			{
				if (m_audioFile)
				{
					ExtAudioFileDispose(m_audioFile);
				}
			}
			
			bool init(const FilePath& path)
			{
				const std::string pathUTF8 = path.toUTF8();
				CFURLRef url = CFURLCreateFromFileSystemRepresentation(kCFAllocatorDefault, (const uint8*)pathUTF8.c_str(), pathUTF8.size(), FALSE);
				if (ExtAudioFileOpenURL(url, &m_audioFile) != noErr)
				{
					return false;
				}
				CFRelease(url);
				
				UInt32 size = sizeof(AudioStreamBasicDescription);
				if (ExtAudioFileGetProperty(m_audioFile,
											kExtAudioFileProperty_FileDataFormat,
											&size,
											&m_inputFormat) != noErr)
				{
					return false;
				}
				
				m_outputFormat.mSampleRate         = m_inputFormat.mSampleRate;
				m_outputFormat.mFormatID           = kAudioFormatLinearPCM;
				m_outputFormat.mFormatFlags        = kAudioFormatFlagIsFloat | kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked;
				m_outputFormat.mChannelsPerFrame   = 2;
				m_outputFormat.mBytesPerPacket     = 2 * sizeof(float);
				m_outputFormat.mBytesPerFrame      = 2 * sizeof(float);
				m_outputFormat.mFramesPerPacket    = 1;
				m_outputFormat.mBitsPerChannel     = 8 * sizeof(float);
				m_outputFormat.mReserved           = 0;

				if (ExtAudioFileSetProperty(m_audioFile,
											kExtAudioFileProperty_ClientDataFormat,
											sizeof(m_outputFormat),
											&m_outputFormat) != noErr)
				{
					return false;
				}
				
				SInt64 frameLength = 0;
				size = sizeof(SInt64);
				if (ExtAudioFileGetProperty(m_audioFile,
											kExtAudioFileProperty_FileLengthFrames,
											&size,
											&frameLength) != noErr)
				{
					return false;
				}
				
				AudioConverterRef acRef = nullptr;
				size = sizeof(AudioConverterRef);
				if (ExtAudioFileGetProperty(m_audioFile, kExtAudioFileProperty_AudioConverter, &size, &acRef) != noErr)
				{
					return false;
				}

				AudioConverterPrimeInfo primeInfo = {};
				UInt32 headerFrames = 0;
				size = sizeof(AudioConverterPrimeInfo);
				if(AudioConverterGetProperty(acRef,
											 kAudioConverterPrimeInfo,
											 &size,
											 &primeInfo) != kAudioConverterErr_PropertyNotSupported)
				{
					headerFrames = primeInfo.leadingFrames;
				}

				m_frameLength = static_cast<size_t>(frameLength);

				if (m_inputFormat.mChannelsPerFrame == 1)
				{
					SInt32 channelMap[2] = {0, 0};
					AudioConverterSetProperty(acRef, kAudioConverterChannelMap,
											  sizeof(channelMap), channelMap);
				}

				ExtAudioFileSeek(m_audioFile, headerFrames);
				
				return true;
			}
			
			Wave load()
			{
				if (m_frameLength == 0)
				{
					return Wave();
				}
				
				Wave wave(m_frameLength, Arg::samplingRate = static_cast<uint32>(m_outputFormat.mSampleRate));

				read(m_frameLength * m_inputFormat.mChannelsPerFrame, wave.data());
				
				float min = -1.0f, max = 1.0f;
				
				for (const auto& sample : wave)
				{
					if (sample.left < min)
					{
						min = sample.left;
					}
					else if (max < sample.left)
					{
						max = sample.left;
					}
					
					if (sample.right < min)
					{
						min = sample.right;
					}
					else if (max < sample.right)
					{
						max = sample.right;
					}
				}
				
				const float scale = 1.0f / std::max(std::abs(min), max);
				
				if (scale < 1.0)
				{
					for (auto& sample : wave)
					{
						sample.left *= scale;
						sample.right *= scale;
					}
				}
				
				return wave;
			}
		};
	}
	
	AudioFormat_AAC::AudioFormat_AAC()
	{

	}

	AudioFormat_AAC::~AudioFormat_AAC()
	{

	}

	AudioFormat AudioFormat_AAC::format() const
	{
		return AudioFormat::AAC;
	}

	const Array<String>& AudioFormat_AAC::possibleExtexsions() const
	{
		static const Array<String> extensions = { U"m4a" };

		return extensions;
	}

	bool AudioFormat_AAC::isHeader(const uint8(&bytes)[16]) const
	{
		// M4V MPEG-4 video/QuickTime file
		static constexpr uint8 M4V_SIGNx[] = { 0x66, 0x74, 0x79, 0x70, 0x6D, 0x70, 0x34, 0x32 };

		// M4A Apple Lossless Audio Codec file
		static constexpr uint8 M4A_SIGNx[] = { 0x66, 0x74, 0x79, 0x70, 0x4D, 0x34, 0x41, 0x20 };

		// MP4 ftypisom
		static constexpr uint8 MP4ISOM_SIGNx[] = { 0x66, 0x74, 0x79, 0x70, 0x69, 0x73, 0x6F, 0x6D };

		return (::memcmp(bytes + 4, M4V_SIGNx, sizeof(M4V_SIGNx)) == 0
			|| ::memcmp(bytes + 4, M4A_SIGNx, sizeof(M4A_SIGNx)) == 0
			|| ::memcmp(bytes + 4, MP4ISOM_SIGNx, sizeof(MP4ISOM_SIGNx)) == 0);
	}
	
	Wave AudioFormat_AAC::decodeFromFile(const FilePath& path) const
	{
		detail::AACDecoder decoder;
		
		if (!decoder.init(path))
		{
			return Wave();
		}

		return decoder.load();
	}

	Wave AudioFormat_AAC::decode(IReader&) const
	{
		// not supported
		return Wave();
	}
}

# endif
