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

namespace s3d
{
	template <class Key, class Value>
	inline void swap(HashTable<Key, Value>& a, HashTable<Key, Value>& b) noexcept
	{
		a.swap(b);
	}

	template <class Key, class Value>
	inline void Formatter(FormatData& formatData, const HashTable<Key, Value>& table)
	{
		formatData.string.append(U"{\n"_sv);

		for (auto [key, value] : table)
		{
			formatData.string.append(U"\t{"_sv);

			Formatter(formatData, key);

			formatData.string.append(U":\t"_sv);

			Formatter(formatData, value);

			formatData.string.append(U"},\n"_sv);
		}

		formatData.string.push_back(U'}');
	}
}
