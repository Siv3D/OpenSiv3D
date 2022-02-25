//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "HashTable.hpp"

namespace s3d
{
	class TimeProfiler
	{
	public:

		TimeProfiler() = default;

		TimeProfiler(const String& name);

		void begin(StringView name);

		void end(StringView name);

		void log() const;

		void console() const;

		void print() const;

	private:

		static constexpr size_t BufferSize = 100;

		struct Data
		{
			uint32 index = 0;

			uint32 ringBufferIndex = 0;

			uint64 beginNS = 0;

			Array<uint32> buffer{ Arg::reserve = BufferSize };
		};

		String m_name;

		HashTable<String, Data> m_data;

		void getData(Array<std::pair<String, Data>>& ordered, size_t& maxLabelLength) const;
	};
}
