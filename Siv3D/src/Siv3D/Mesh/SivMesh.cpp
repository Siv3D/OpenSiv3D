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

# include <Siv3D/Mesh.hpp>
# include <Siv3D/Transformer3D.hpp>
# include <Siv3D/Mesh/IMesh.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Renderer3D/IRenderer3D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Troubleshooting/Troubleshooting.hpp>

namespace s3d
{
	namespace detail
	{
		static void CheckEngine(const StringView type = U"Mesh")
		{
			if (not Siv3DEngine::isActive())
			{
				Troubleshooting::Show(Troubleshooting::Error::AssetInitializationBeforeEngineStartup, type);
				std::exit(EXIT_FAILURE);
			}
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Mesh>>::AssetIDWrapper()
	{
		detail::CheckEngine();
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
		: AssetHandle{ (detail::CheckEngine(), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Mesh)->create(meshData))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Mesh::Mesh(Dynamic, const size_t vertexCount, const size_t triangleCount)
		: AssetHandle{ (detail::CheckEngine(U"DynamicMesh"), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Mesh)->createDynamic(vertexCount, triangleCount)))}
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Mesh::Mesh(Dynamic, const MeshData& meshData)
		: AssetHandle{ (detail::CheckEngine(U"DynamicMesh"), std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Mesh)->createDynamic(meshData))) }
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

	Sphere Mesh::boundingSphere() const
	{
		return SIV3D_ENGINE(Mesh)->getBoundingSphere(m_handle->id());
	}

	Box Mesh::boundingBox() const
	{
		return SIV3D_ENGINE(Mesh)->getBoundingBox(m_handle->id());
	}

	void Mesh::draw(const ColorF& color) const
	{
		const uint32 startIndex = 0;

		const uint32 indexCount = static_cast<uint32>(SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addMesh(startIndex, indexCount, *this, PhongMaterial{ color, HasDiffuseTexture::No });
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

		const Transformer3D transformer{ mat };

		SIV3D_ENGINE(Renderer3D)->addMesh(startIndex, indexCount, *this, PhongMaterial{ color, HasDiffuseTexture::No });
	}


	void Mesh::draw(const PhongMaterial& material) const
	{
		const uint32 startIndex = 0;

		const uint32 indexCount = static_cast<uint32>(SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addMesh(startIndex, indexCount, *this, material);
	}

	void Mesh::draw(const double x, const double y, const double z, const PhongMaterial& material) const
	{
		draw(Mat4x4::Translate(x, y, z), material);
	}

	void Mesh::draw(const Vec3& pos, const PhongMaterial& material) const
	{
		draw(Mat4x4::Translate(pos), material);
	}

	void Mesh::draw(const double x, const double y, const double z, const Quaternion& rotation, const PhongMaterial& material) const
	{
		draw(Mat4x4::Rotate(rotation).translated(x, y, z), material);
	}

	void Mesh::draw(const Vec3& pos, const Quaternion& rotation, const PhongMaterial& material) const
	{
		draw(Mat4x4::Rotate(rotation).translated(pos), material);
	}

	void Mesh::draw(const Mat4x4& mat, const PhongMaterial& material) const
	{
		const uint32 startIndex = 0;

		const uint32 indexCount = static_cast<uint32>(SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		const Transformer3D transformer{ mat };

		SIV3D_ENGINE(Renderer3D)->addMesh(startIndex, indexCount, *this, material);
	}


	void Mesh::draw(const Texture& texture, const ColorF& color) const
	{
		const uint32 startIndex = 0;

		const uint32 indexCount = static_cast<uint32>(SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, texture, PhongMaterial{ color, HasDiffuseTexture::Yes });
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

		const Transformer3D transformer{ mat };

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, texture, PhongMaterial{ color, HasDiffuseTexture::Yes });
	}


	void Mesh::draw(const Texture& texture, const PhongMaterial& material) const
	{
		const uint32 startIndex = 0;

		const uint32 indexCount = static_cast<uint32>(SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, texture, material);
	}

	void Mesh::draw(const double x, const double y, const double z, const Texture& texture, const PhongMaterial& material) const
	{
		draw(Mat4x4::Translate(x, y, z), texture, material);
	}

	void Mesh::draw(const Vec3& pos, const Texture& texture, const PhongMaterial& material) const
	{
		draw(Mat4x4::Translate(pos), texture, material);
	}

	void Mesh::draw(const double x, const double y, const double z, const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const
	{
		draw(Mat4x4::Rotate(rotation).translated(x, y, z), texture, material);
	}

	void Mesh::draw(const Vec3& pos, const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const
	{
		draw(Mat4x4::Rotate(rotation).translated(pos), texture, material);
	}

	void Mesh::draw(const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const
	{
		const uint32 startIndex = 0;

		const uint32 indexCount = static_cast<uint32>(SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		const Transformer3D transformer{ mat };

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, texture, material);
	}


	void Mesh::draw(const TextureRegion& textureRegion, const ColorF& color) const
	{
		const uint32 startIndex = 0;

		const uint32 indexCount = static_cast<uint32>(SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, textureRegion, PhongMaterial{ color, HasDiffuseTexture::Yes });
	}

	void Mesh::draw(const double x, const double y, const double z, const TextureRegion& textureRegion, const ColorF& color) const
	{
		draw(Mat4x4::Translate(x, y, z), textureRegion, color);
	}

	void Mesh::draw(const Vec3& pos, const TextureRegion& textureRegion, const ColorF& color) const
	{
		draw(Mat4x4::Translate(pos), textureRegion, color);
	}

	void Mesh::draw(const double x, const double y, const double z, const Quaternion& rotation, const TextureRegion& textureRegion, const ColorF& color) const
	{
		draw(Mat4x4::Rotate(rotation).translated(x, y, z), textureRegion, color);
	}

	void Mesh::draw(const Vec3& pos, const Quaternion& rotation, const TextureRegion& textureRegion, const ColorF& color) const
	{
		draw(Mat4x4::Rotate(rotation).translated(pos), textureRegion, color);
	}

	void Mesh::draw(const Mat4x4& mat, const TextureRegion& textureRegion, const ColorF& color) const
	{
		const uint32 startIndex = 0;

		const uint32 indexCount = static_cast<uint32>(SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		const Transformer3D transformer{ mat };

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, textureRegion, PhongMaterial{ color, HasDiffuseTexture::Yes });
	}


	void Mesh::draw(const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		const uint32 startIndex = 0;

		const uint32 indexCount = static_cast<uint32>(SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, textureRegion, material);
	}

	void Mesh::draw(const double x, const double y, const double z, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		draw(Mat4x4::Translate(x, y, z), textureRegion, material);
	}

	void Mesh::draw(const Vec3& pos, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		draw(Mat4x4::Translate(pos), textureRegion, material);
	}

	void Mesh::draw(const double x, const double y, const double z, const Quaternion& rotation, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		draw(Mat4x4::Rotate(rotation).translated(x, y, z), textureRegion, material);
	}

	void Mesh::draw(const Vec3& pos, const Quaternion& rotation, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		draw(Mat4x4::Rotate(rotation).translated(pos), textureRegion, material);
	}

	void Mesh::draw(const Mat4x4& mat, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		const uint32 startIndex = 0;

		const uint32 indexCount = static_cast<uint32>(SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		const Transformer3D transformer{ mat };

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, textureRegion, material);
	}


	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const ColorF& color) const
	{
		const uint32 startIndex = (startTriangle * 3);

		const uint32 indexCount = (triangleCount * 3);

		assert((startIndex + indexCount) <= SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addMesh(startIndex, indexCount, *this, PhongMaterial{ color, HasDiffuseTexture::No });
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

		assert((startIndex + indexCount) <= SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		const Transformer3D transformer{ mat };

		SIV3D_ENGINE(Renderer3D)->addMesh(startIndex, indexCount, *this, PhongMaterial{ color, HasDiffuseTexture::No });
	}


	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const PhongMaterial& material) const
	{
		const uint32 startIndex = (startTriangle * 3);

		const uint32 indexCount = (triangleCount * 3);

		assert((startIndex + indexCount) <= SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addMesh(startIndex, indexCount, *this, material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const double x, const double y, const double z, const PhongMaterial& material) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Translate(x, y, z), material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Vec3& pos, const PhongMaterial& material) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Translate(pos), material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const double x, const double y, const double z, const Quaternion& rotation, const PhongMaterial& material) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Rotate(rotation).translated(x, y, z), material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const PhongMaterial& material) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Rotate(rotation).translated(pos), material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Mat4x4& mat, const PhongMaterial& material) const
	{
		const uint32 startIndex = (startTriangle * 3);

		const uint32 indexCount = (triangleCount * 3);

		assert((startIndex + indexCount) <= SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		const Transformer3D transformer{ mat };

		SIV3D_ENGINE(Renderer3D)->addMesh(startIndex, indexCount, *this, material);
	}


	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Texture& texture, const ColorF& color) const
	{
		const uint32 startIndex = (startTriangle * 3);

		const uint32 indexCount = (triangleCount * 3);

		assert((startIndex + indexCount) <= SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, texture, PhongMaterial{ color, HasDiffuseTexture::Yes });
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

		assert((startIndex + indexCount) <= SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		const Transformer3D transformer{ mat };

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, texture, PhongMaterial{ color, HasDiffuseTexture::Yes });
	}


	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Texture& texture, const PhongMaterial& material) const
	{
		const uint32 startIndex = (startTriangle * 3);

		const uint32 indexCount = (triangleCount * 3);

		assert((startIndex + indexCount) <= SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, texture, material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const double x, const double y, const double z, const Texture& texture, const PhongMaterial& material) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Translate(x, y, z), texture, material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Vec3& pos, const Texture& texture, const PhongMaterial& material) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Translate(pos), texture, material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const double x, const double y, const double z, const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Rotate(rotation).translated(x, y, z), texture, material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Rotate(rotation).translated(pos), texture, material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const
	{
		const uint32 startIndex = (startTriangle * 3);

		const uint32 indexCount = (triangleCount * 3);

		assert((startIndex + indexCount) <= SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		const Transformer3D transformer{ mat };

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, texture, material);
	}


	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const TextureRegion& textureRegion, const ColorF& color) const
	{
		const uint32 startIndex = (startTriangle * 3);

		const uint32 indexCount = (triangleCount * 3);

		assert((startIndex + indexCount) <= SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, textureRegion, PhongMaterial{ color, HasDiffuseTexture::Yes });
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const double x, const double y, const double z, const TextureRegion& textureRegion, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Translate(x, y, z), textureRegion, color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Vec3& pos, const TextureRegion& textureRegion, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Translate(pos), textureRegion, color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const double x, const double y, const double z, const Quaternion& rotation, const TextureRegion& textureRegion, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Rotate(rotation).translated(x, y, z), textureRegion, color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const TextureRegion& textureRegion, const ColorF& color) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Rotate(rotation).translated(pos), textureRegion, color);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Mat4x4& mat, const TextureRegion& textureRegion, const ColorF& color) const
	{
		const uint32 startIndex = (startTriangle * 3);

		const uint32 indexCount = (triangleCount * 3);

		assert((startIndex + indexCount) <= SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		const Transformer3D transformer{ mat };

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, textureRegion, PhongMaterial{ color, HasDiffuseTexture::Yes });
	}


	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		const uint32 startIndex = (startTriangle * 3);

		const uint32 indexCount = (triangleCount * 3);

		assert((startIndex + indexCount) <= SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, textureRegion, material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const double x, const double y, const double z, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Translate(x, y, z), textureRegion, material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Vec3& pos, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Translate(pos), textureRegion, material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const double x, const double y, const double z, const Quaternion& rotation, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Rotate(rotation).translated(x, y, z), textureRegion, material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		drawSubset(startTriangle, triangleCount, Mat4x4::Rotate(rotation).translated(pos), textureRegion, material);
	}

	void Mesh::drawSubset(const uint32 startTriangle, const uint32 triangleCount, const Mat4x4& mat, const TextureRegion& textureRegion, const PhongMaterial& material) const
	{
		const uint32 startIndex = (startTriangle * 3);

		const uint32 indexCount = (triangleCount * 3);

		assert((startIndex + indexCount) <= SIV3D_ENGINE(Mesh)->getIndexCount(m_handle->id()));

		const Transformer3D transformer{ mat };

		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(startIndex, indexCount, *this, textureRegion, material);
	}


	void Mesh::swap(Mesh& other) noexcept
	{
		m_handle.swap(other.m_handle);
	}
}
