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

# include <Siv3D/Platform.hpp>

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4100)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4305)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4456)
# define PAR_SHAPES_IMPLEMENTATION
# define _CRT_SECURE_NO_WARNINGS
# include <par_shapes/par_shapes.h>
# undef _CRT_SECURE_NO_WARNINGS
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()

# include <Siv3D/Sphere.hpp>
# include <Siv3D/Mat4x4.hpp>
# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3DEngine.hpp>
# include <Renderer2D/IRenderer2D.hpp>


namespace s3d
{
	void Sphere::draw(const Mat4x4& vp, const ColorF& color) const
	{
		const Float2 resolution = Graphics2D::GetRenderTargetSize();
		const Float4 colorF = color.toFloat4();

	}
}
