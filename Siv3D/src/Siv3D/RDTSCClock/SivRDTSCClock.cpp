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

# include <Siv3D/RDTSCClock.hpp>
# include <Siv3D/Logger.hpp>
# include <Siv3D/Console.hpp>
# include <Siv3D/Print.hpp>

namespace s3d
{
	void RDTSCClock::log() const
	{
		const auto c = cycles();

		Logger(c, U"cycles"_sv);
	}

	void RDTSCClock::console() const
	{
		const auto c = cycles();

		Console(c, U"cycles"_sv);
	}

	void RDTSCClock::print() const
	{
		const auto c = cycles();

		Print(c, U"cycles"_sv);
	}
}
