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

# pragma once
# include <Siv3D/EngineLog.hpp>
# include <AudioToolBox/AudioFile.h>
# include <AudioToolBox/AudioConverter.h>
# include <AudioToolbox/ExtendedAudioFile.h>

namespace s3d
{
	namespace detail
	{
		class AudioFileDecoder
		{
		public:
			
			~AudioFileDecoder()
			{
				if (m_audioFile)
				{
					ExtAudioFileDispose(m_audioFile);
				}
			}
			
			bool init(const FilePath& path)
			{
				LOG_TRACE(U"AudioFileDecoder::init()");
				
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
				
				Wave wave(m_frameLength, Arg::sampleRate = static_cast<uint32>(m_outputFormat.mSampleRate));
				
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
					
					if (numFrames == 0)
					{
						break;
					}
					
					framesRead += numFrames;
				}
				
				return framesRead * m_outputFormat.mChannelsPerFrame;
			}
		};
	}
}
