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
# include <Siv3D/Mesh.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/RenderTexture.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DRenderer3D
	{
	public:

		static ISiv3DRenderer3D* Create();

		virtual ~ISiv3DRenderer3D() = default;

		virtual void init() = 0;

		virtual void addMesh(const Mesh& mesh, const Mat4x4& mat, const Float4& color) {}

		virtual void addTexturedMesh(const Mesh& mesh, const Texture& texture, const Mat4x4& mat, const Float4& color) {}

		virtual void setCameraTransform(const Mat4x4& matrix) {}

		virtual void setRenderTarget(const Optional<RenderTexture>& rt) {}

		virtual Optional<RenderTexture> getRenderTarget() const { return none; }


		virtual void flush() {}
	};
}
