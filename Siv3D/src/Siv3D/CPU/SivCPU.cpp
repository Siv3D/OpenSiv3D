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
# include "ICPU.hpp"

namespace s3d
{
	namespace CPU
	{
		const CPUFeature& GetFeature()
		{
			return Siv3DEngine::Get<ISiv3DCPU>()->getFeature();
		}

		void SetFeature(const CPUFeature& feature)
		{
			Siv3DEngine::Get<ISiv3DCPU>()->setFeature(feature);
		}
	}
}
