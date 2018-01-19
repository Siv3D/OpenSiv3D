//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "../Siv3DEngine.hpp"
# include "ICPU.hpp"

namespace s3d
{
	namespace CPU
	{
		const CPUFeature& GetFeature()
		{
			return Siv3DEngine::GetCPU()->getFeature();
		}

		void SetFeature(const CPUFeature& feature)
		{
			Siv3DEngine::GetCPU()->setFeature(feature);
		}
	}
}
