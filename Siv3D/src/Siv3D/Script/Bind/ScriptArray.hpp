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
# include <Siv3D/Script.hpp>
# include "../angelscript/scriptarray.h"

namespace s3d
{
	using namespace AngelScript;

	namespace detail
	{
		template <class Type>
		static Array<Type> FromScriptArray(const CScriptArray* arr)
		{
			Array<Type> result(arr->GetSize());

			for (uint32 i = 0; i < result.size(); ++i)
			{
				result[i] = *static_cast<const Type*>(arr->At(i));
			}

			return result;
		}
	}
}
