//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2017 Ryo Suzuki
//	Copyright (C) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Fwd.hpp>

namespace s3d
{
	class ISiv3DLogger
	{
	public:

		static ISiv3DLogger* Create();

		virtual ~ISiv3DLogger() = default;

		virtual bool init() = 0;

		virtual void write(LogDescription desc, const String& str) = 0;

		//virtual void write(LogDescription desc, const Image& image, const String& str) = 0;

		//virtual void writeRaw(const String& str) = 0;

		//virtual void writeOnce(LogDescription desc, const String& str, int32 id) = 0;

		//virtual void writeOnce(LogDescription desc, const Image& image, const String& str, int32 id) = 0;

		//virtual const wchar* getMessage(uint32 index) const = 0;
	};
}
