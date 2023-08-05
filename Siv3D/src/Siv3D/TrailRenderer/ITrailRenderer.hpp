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
# include <Siv3D/Common.hpp>

namespace s3d
{
	class Trail;
	class Texture;

	class SIV3D_NOVTABLE ISiv3DTrailRenderer
	{
	public:

		static ISiv3DTrailRenderer* Create();

		virtual ~ISiv3DTrailRenderer() = default;

		virtual void draw(const Trail& trail) = 0;

		virtual void draw(const Trail& trail, const Texture& texture) = 0;
	};
}
