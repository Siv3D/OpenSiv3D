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

# include <Siv3D/Mesh.hpp>
# include <Siv3D/Mesh/IMesh.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Renderer3D/IRenderer3D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<Mesh>>::AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`Mesh` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Mesh>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Mesh))
		{
			p->release(m_id);
		}
	}

	Mesh::Mesh() {}

	Mesh::Mesh(const Array<Vertex3D>& vertices, const Array<Vertex3D::IndexType>& indices)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Mesh)->create(vertices, indices)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Mesh::~Mesh() {}

	size_t Mesh::num_triangles() const
	{
		return (SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()) / 3);
	}

	void Mesh::draw(const Vec3& pos, const ColorF& color) const
	{
		draw(Mat4x4::Translate(pos), color);
	}

	void Mesh::draw(const Mat4x4& mat, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer3D)->addMesh(*this, mat, color.toFloat4());
	}
}
