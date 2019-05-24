//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3DEngine.hpp>
# include <Siv3D/Print.hpp>
# include "IPrint.hpp"

namespace s3d
{
	namespace detail
	{
		PrintBuffer::PrintBuffer()
			: formatData(std::make_unique<FormatData>())
		{

		}

		PrintBuffer::PrintBuffer(PrintBuffer&& other)
			: formatData(std::move(other.formatData))
		{

		}

		PrintBuffer::~PrintBuffer()
		{
			if (formatData)
			{
				Print.writeln(formatData->string);
			}
		}

		void Print_impl::writeln(const String& text) const
		{
			Siv3DEngine::Get<ISiv3DPrint>()->add(text);
		}

		void Print_impl::operator()(const String& text) const
		{
			writeln(text);
		}
	}

	void ClearPrint()
	{
		Siv3DEngine::Get<ISiv3DPrint>()->clear();
	}
}
