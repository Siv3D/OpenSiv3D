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
	template <class ForwardIt>
	inline void Formatter(FormatData& formatData, ForwardIt first, ForwardIt last)
	{
		formatData.string.push_back(U'{');

		bool isFirst = true;

		while (first != last)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				formatData.string.append(U", "_sv);
			}

			Formatter(formatData, *first);

			++first;
		}

		formatData.string.push_back(U'}');
	}

	template <class Type, size_t N>
	inline void Formatter(FormatData& formatData, const Type(&values)[N])
	{
		Formatter(formatData, std::begin(values), std::end(values));
	}

	template <class Type, size_t N>
	inline void Formatter(FormatData& formatData, const std::array<Type, N>& v)
	{
		Formatter(formatData, v.begin(), v.end());
	}

	template <class Type, class Allocator>
	inline void Formatter(FormatData& formatData, const std::vector<Type, Allocator>& v)
	{
		Formatter(formatData, v.begin(), v.end());
	}

	template <class Type>
	inline void Formatter(FormatData& formatData, const std::initializer_list<Type>& ilist)
	{
		Formatter(formatData, ilist.begin(), ilist.end());
	}

	template <class Fitrst, class Second>
	inline void Formatter(FormatData& formatData, const std::pair<Fitrst, Second>& pair)
	{
		formatData.string.push_back(U'{');
		Formatter(formatData, pair.first);
		formatData.string.append(U", "_sv);
		Formatter(formatData, pair.second);
		formatData.string.push_back(U'}');
	}
}
