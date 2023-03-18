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
# include <Siv3D/AudioCodec/IAudioCodec.hpp>

namespace s3d
{
	class CAudioCodec final : public ISiv3DAudioCodec
	{
	public:

		CAudioCodec();

		~CAudioCodec() override;

		void init() override;
	
		Wave decode(IReader& reader, AudioFormat audioFormat) override;
		
		bool encode(const Wave& wave, IWriter& writer, AudioFormat audioFormat) override;
		
		//
		//	macOS
		//
		
		Wave decode(FilePathView path, AudioFormat audioFormat);
	};
}
