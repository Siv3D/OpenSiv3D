//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Texture/ITexture.hpp>

namespace s3d
{
	class CTexture_Null final : public ISiv3DTexture
	{
	private:

	public:

		CTexture_Null();

		~CTexture_Null() override;

		void init() override;

		bool update() override;
	};
}
