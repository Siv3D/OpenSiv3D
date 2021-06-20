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
# include <Siv3D/Renderer3D/IRenderer3D.hpp>

namespace s3d
{
	class CRenderer3D_Null final : public ISiv3DRenderer3D
	{
	public:

		CRenderer3D_Null();

		~CRenderer3D_Null() override;

		void init() override;

	private:

	};
}
