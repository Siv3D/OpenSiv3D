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

# pragma once
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include "IAudio.hpp"
# include "AudioData.hpp"
# include "AudioBus.hpp"

namespace s3d
{
	class CAudio final : public ISiv3DAudio
	{
	public:

		CAudio();

		~CAudio();

		void init() override;

		void release(Audio::IDType handleID) override;

	private:

		std::unique_ptr<SoLoud::Soloud> m_soloud;
		
		std::array<std::unique_ptr<AudioBus>, Audio::MaxBusCount> m_buses;

		AssetHandleManager<Audio::IDType, AudioData> m_audios{ U"Audio" };
	};
}
