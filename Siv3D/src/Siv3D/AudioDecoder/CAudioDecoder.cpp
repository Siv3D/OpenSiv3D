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

# include <Siv3D/FileSystem.hpp>
# include "CAudioDecoder.hpp"
# include <Siv3D/EngineLog.hpp>
//# include <Siv3D/AudioFormat/WAVEDecoder.hpp>

namespace s3d
{
	CAudioDecoder::~CAudioDecoder()
	{
		LOG_SCOPED_TRACE(U"CAudioDecoder::~CAudioDecoder()");
	}

	void CAudioDecoder::init()
	{
		LOG_SCOPED_TRACE(U"CAudioDecoder::init()");

		//m_decoders.push_back(std::make_unique<WAVEDecoder>());
	}

	//Optional<AudioInfo> CAudioDecoder::getAudioInfo(IReader& reader, const FilePathView pathHint, const AudioFormat imageFormat)
	//{
	//	LOG_SCOPED_TRACE(U"CAudioDecoder::getAudioInfo()");

	//	auto it = findDecoder(imageFormat);

	//	if (it == m_decoders.end())
	//	{
	//		it = findDecoder(reader, pathHint);

	//		if (it == m_decoders.end())
	//		{
	//			return{};
	//		}
	//	}

	//	LOG_TRACE(U"Audio decoder name: {}"_fmt((*it)->name()));

	//	return (*it)->getAudioInfo(reader, pathHint);
	//}

	//Wave CAudioDecoder::decode(IReader& reader, const FilePathView pathHint, const AudioFormat imageFormat)
	//{
	//	LOG_SCOPED_TRACE(U"CAudioDecoder::decode()");

	//	auto it = findDecoder(imageFormat);

	//	if (it == m_decoders.end())
	//	{
	//		it = findDecoder(reader, pathHint);

	//		if (it == m_decoders.end())
	//		{
	//			return{};
	//		}
	//	}

	//	LOG_TRACE(U"Audio decoder name: {}"_fmt((*it)->name()));

	//	return (*it)->decode(reader, pathHint);
	//}

	//bool CAudioDecoder::add(std::unique_ptr<IAudioDecoder>&& decoder)
	//{
	//	const StringView name = decoder->name();

	//	const bool exisits = m_decoders.includes_if([name](const std::unique_ptr<IAudioDecoder>& decoder)
	//		{
	//			return decoder->name() == name;
	//		});

	//	if (exisits)
	//	{
	//		return false;
	//	}

	//	m_decoders.push_back(std::move(decoder));

	//	return true;
	//}

	//void CAudioDecoder::remove(const StringView name)
	//{
	//	m_decoders.remove_if([name](const std::unique_ptr<IAudioDecoder>& decoder)
	//		{
	//			return decoder->name() == name;
	//		});
	//}

	//const Array<std::unique_ptr<IAudioDecoder>>& CAudioDecoder::enumDecoder() const noexcept
	//{
	//	return m_decoders;
	//}

	//Array<std::unique_ptr<IAudioDecoder>>::const_iterator CAudioDecoder::findDecoder(const AudioFormat imageFormat) const
	//{
	//	if (imageFormat == AudioFormat::Unknown)
	//	{
	//		return m_decoders.end();
	//	}

	//	for (auto it = m_decoders.begin(); it != m_decoders.end(); ++it)
	//	{
	//		if ((*it)->imageFormat() == imageFormat)
	//		{
	//			return it;
	//		}
	//	}

	//	return m_decoders.end();
	//}

	//Array<std::unique_ptr<IAudioDecoder>>::const_iterator CAudioDecoder::findDecoder(const IReader& reader, const FilePathView pathHint) const
	//{
	//	if (not reader.isOpen())
	//	{
	//		return m_decoders.end();
	//	}

	//	if (not reader.supportsLookahead())
	//	{
	//		return m_decoders.end();
	//	}

	//	uint8 header[16] = {};

	//	if (not reader.lookahead(header))
	//	{
	//		return m_decoders.end();
	//	}

	//	for (auto it = m_decoders.begin(); it != m_decoders.end(); ++it)
	//	{
	//		if ((*it)->isHeader(header))
	//		{
	//			return it;
	//		}
	//	}

	//	if (pathHint)
	//	{
	//		const String extension = FileSystem::Extension(pathHint);

	//		for (auto it = m_decoders.begin(); it != m_decoders.end(); ++it)
	//		{
	//			if ((*it)->possibleExtensions().includes(extension))
	//			{
	//				return it;
	//			}
	//		}
	//	}

	//	return m_decoders.end();
	//}
}
