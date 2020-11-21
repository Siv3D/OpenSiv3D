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
# include "Common.hpp"
# include "Optional.hpp"
# include "VertexShader.hpp"
# include "PixelShader.hpp"

namespace s3d
{
	namespace Graphics2D
	{
		[[nodiscard]]
		Optional<VertexShader> GetCustomVertexShader();

		[[nodiscard]]
		Optional<PixelShader> GetCustomPixelShader();

		void DrawTriangles(uint32 count);

		namespace Internal
		{
			void SetCustomVertexShader(const Optional<VertexShader>& vs);

			void SetCustomPixelShader(const Optional<PixelShader>& ps);
		}
	}
}
