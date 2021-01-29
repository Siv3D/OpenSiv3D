//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Texture/ITexture.hpp>

namespace s3d
{
	class CTexture_Metal final : public ISiv3DTexture
	{
	private:

	public:

		CTexture_Metal();

		~CTexture_Metal() override;

		void updateAsyncTextureLoad(size_t maxUpdate) override;
	};
}
