//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "IAudio.hpp"
# include "../Profiler/IProfiler.hpp"

namespace s3d
{
	template <>
	AssetHandle<Audio::Handle>::~AssetHandle()
	{
		if (!Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = Siv3DEngine::GetAudio())
		{
			p->release(m_id);
		}
	}

	Audio::Audio()
		: m_handle(std::make_shared<AudioHandle>())
	{

	}

	Audio::Audio(const Wave& wave)
		: m_handle(std::make_shared<AudioHandle>(Siv3DEngine::GetAudio()->create(wave)))
	{
		ASSET_CREATION();
	}

	Audio::Audio(const FilePath& path)
		: Audio(Wave(path))
	{

	}

	Audio::~Audio()
	{

	}

	void Audio::release()
	{
		m_handle = std::make_shared<AudioHandle>();
	}

	bool Audio::isEmpty() const
	{
		return m_handle->getID() == AudioHandle::NullID;
	}

	Audio::IDType Audio::id() const
	{
		return m_handle->getID();
	}

	bool Audio::operator ==(const Audio& audio) const
	{
		return m_handle->getID() == audio.m_handle->getID();
	}

	bool Audio::operator !=(const Audio& audio) const
	{
		return m_handle->getID() != audio.m_handle->getID();
	}
}
