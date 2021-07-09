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

	Mesh::Mesh(const MeshData& meshData)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Mesh)->create(meshData)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Mesh::~Mesh() {}

	size_t Mesh::num_vertices() const
	{
		return SIV3D_ENGINE(Mesh)->getVertexCount(m_handle->id());
	}

	size_t Mesh::num_triangles() const
	{
		return (SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()) / 3);
	}

	void Mesh::draw(const ColorF& color) const
	{
		draw(Mat4x4::Identity(), color);
	}

	void Mesh::draw(const double x, const double y, const double z, const ColorF& color) const
	{
		draw(Mat4x4::Translate(x, y, z), color);
	}

	void Mesh::draw(const Vec3& pos, const ColorF& color) const
	{
		draw(Mat4x4::Translate(pos), color);
	}

	void Mesh::draw(const double x, const double y, const double z, const Quaternion& rotation, const ColorF& color) const
	{
		draw(Mat4x4::Rotate(rotation).translated(x, y, z), color);
	}

	void Mesh::draw(const Vec3& pos, const Quaternion& rotation, const ColorF& color) const
	{
		draw(Mat4x4::Rotate(rotation).translated(pos), color);
	}

	void Mesh::draw(const Mat4x4& mat, const ColorF& color) const
	{
		const uint32 startIndex = 0;

		const uint32 indexCount = static_cast<uint32>(SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addMesh(startIndex, indexCount, *this, mat, color.toFloat4());
	}


	void Mesh::draw(const Texture& texture, const ColorF& color) const
	{
		draw(Mat4x4::Identity(), texture, color);
	}

	void Mesh::draw(const double x, const double y, const double z, const Texture& texture, const ColorF& color) const
	{
		draw(Mat4x4::Translate(x, y, z), texture, color);
	}

	void Mesh::draw(const Vec3& pos, const Texture& texture, const ColorF& color) const
	{
		draw(Mat4x4::Translate(pos), texture, color);
	}

	void Mesh::draw(const double x, const double y, const double z, const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		draw(Mat4x4::Rotate(rotation).translated(x, y, z), texture, color);
	}

	void Mesh::draw(const Vec3& pos, const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		draw(Mat4x4::Rotate(rotation).translated(pos), texture, color);
	}

	void Mesh::draw(const Mat4x4& mat, const Texture& texture, const ColorF& color) const
	{
		const uint32 startIndex = 0;

		const uint32 indexCount = static_cast<uint32>(SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, texture, mat, color.toFloat4());
	}


	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Identity(), color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const double x, const double y, const double z, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Translate(x, y, z), color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Vec3& pos, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Translate(pos), color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const double x, const double y, const double z, const Quaternion& rotation, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Rotate(rotation).translated(x, y, z), color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Rotate(rotation).translated(pos), color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Mat4x4& mat, const ColorF& color) const
	{
		const uint32 startIndex = (startTriangle * 3);

		const uint32 indexCount = (triangleCount * 3);

		SIV3D_ENGINE(Renderer3D)->addMesh(startIndex, indexCount, *this, mat, color.toFloat4());
	}



	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Texture& texture, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Identity(), texture, color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const double x, const double y, const double z, const Texture& texture, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Translate(x, y, z), texture, color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Vec3& pos, const Texture& texture, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Translate(pos), texture, color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const double x, const double y, const double z, const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Rotate(rotation).translated(x, y, z), texture, color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const Texture& texture, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Rotate(rotation).translated(pos), texture, color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Mat4x4& mat, const Texture& texture, const ColorF& color) const
	{
		const uint32 startIndex = (startTriangle * 3);

		const uint32 indexCount = (triangleCount * 3);

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, texture, mat, color.toFloat4());
	}
}
