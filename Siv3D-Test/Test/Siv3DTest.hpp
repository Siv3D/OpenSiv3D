//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D.hpp>

namespace s3d
{
	void RunTest();

	void Log(const String& text);

	template <class... Args>
	inline void Log(const Args&... args)
	{
		Log(Format(args...));
	}

# if defined(SIV3D_TARGET_WINDOWS)
	class RDTSC
	{
	private:

		uint64 begin;

	public:

		RDTSC()
			: begin(__rdtsc()) {}

		~RDTSC()
		{
			const auto result = __rdtsc() - begin;

			Log(result, L" cycles");
		}
	};
# endif
}
