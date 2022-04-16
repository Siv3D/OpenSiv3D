//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "Array.hpp"
# include "Vertex3D.hpp"
# include "Mat4x4.hpp"
# include "ColorHSV.hpp"
# include "AssetHandle.hpp"
# include "Sphere.hpp"
# include "Box.hpp"

namespace s3d
{
	struct MeshData;
	class Texture;
	struct TextureRegion;
	struct PhongMaterial;

	class Mesh : public AssetHandle<Mesh>
	{
	public:

		SIV3D_NODISCARD_CXX20
		Mesh();

		SIV3D_NODISCARD_CXX20
		explicit Mesh(const MeshData& meshData);

		virtual ~Mesh();

		[[nodiscard]]
		size_t num_vertices() const;

		[[nodiscard]]
		size_t num_triangles() const;

		[[nodiscard]]
		Sphere boundingSphere() const;

		[[nodiscard]]
		Box boundingBox() const;

		void draw(const ColorF& color = Palette::White) const;

		void draw(double x, double y, double z, const ColorF& color = Palette::White) const;

		void draw(const Vec3& pos, const ColorF& color = Palette::White) const;

		void draw(double x, double y, double z, const Quaternion& rotation, const ColorF& color = Palette::White) const;

		void draw(const Vec3& pos, const Quaternion& rotation, const ColorF& color = Palette::White) const;

		void draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;


		void draw(const PhongMaterial&material) const;

		void draw(double x, double y, double z, const PhongMaterial& material) const;

		void draw(const Vec3& pos, const PhongMaterial& material) const;

		void draw(double x, double y, double z, const Quaternion& rotation, const PhongMaterial& material) const;

		void draw(const Vec3& pos, const Quaternion& rotation, const PhongMaterial& material) const;

		void draw(const Mat4x4& mat, const PhongMaterial& material) const;




		void draw(const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(double x, double y, double z, const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(const Vec3& pos, const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(double x, double y, double z, const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(const Vec3& pos, const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;



		void draw(const Texture& texture, const PhongMaterial& material) const;

		void draw(double x, double y, double z, const Texture& texture, const PhongMaterial& material) const;

		void draw(const Vec3& pos, const Texture& texture, const PhongMaterial& material) const;

		void draw(double x, double y, double z, const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const;

		void draw(const Vec3& pos, const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const;

		void draw(const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const;




		void draw(const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;

		void draw(double x, double y, double z, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;

		void draw(const Vec3& pos, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;

		void draw(double x, double y, double z, const Quaternion& rotation, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;

		void draw(const Vec3& pos, const Quaternion& rotation, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;

		void draw(const Mat4x4& mat, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;



		void draw(const TextureRegion& textureRegion, const PhongMaterial& material) const;

		void draw(double x, double y, double z, const TextureRegion& textureRegion, const PhongMaterial& material) const;

		void draw(const Vec3& pos, const TextureRegion& textureRegion, const PhongMaterial& material) const;

		void draw(double x, double y, double z, const Quaternion& rotation, const TextureRegion& textureRegion, const PhongMaterial& material) const;

		void draw(const Vec3& pos, const Quaternion& rotation, const TextureRegion& textureRegion, const PhongMaterial& material) const;

		void draw(const Mat4x4& mat, const TextureRegion& textureRegion, const PhongMaterial& material) const;



		void drawSubset(uint32 startTriangle, uint32 triangleCount, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const Quaternion& rotation, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Mat4x4& mat, const ColorF& color = Palette::White) const;


		void drawSubset(uint32 startTriangle, uint32 triangleCount, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const Quaternion& rotation, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Mat4x4& mat, const PhongMaterial& material) const;


		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;


		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Texture& texture, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const Texture& texture, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const Texture& texture, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const Texture& texture, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Mat4x4& mat, const Texture& texture, const PhongMaterial& material) const;


		void drawSubset(uint32 startTriangle, uint32 triangleCount, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const Quaternion& rotation, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Mat4x4& mat, const TextureRegion& textureRegion, const ColorF& color = Palette::White) const;


		void drawSubset(uint32 startTriangle, uint32 triangleCount, const TextureRegion& textureRegion, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const TextureRegion& textureRegion, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const TextureRegion& textureRegion, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const Quaternion& rotation, const TextureRegion& textureRegion, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const TextureRegion& textureRegion, const PhongMaterial& material) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Mat4x4& mat, const TextureRegion& textureRegion, const PhongMaterial& material) const;


		void swap(Mesh& other) noexcept;


	protected:

		struct Dynamic {};

		SIV3D_NODISCARD_CXX20
		Mesh(Dynamic, size_t vertexCount, size_t triangleCount);

		SIV3D_NODISCARD_CXX20
		Mesh(Dynamic, const MeshData& meshData);
	};
}

template <>
inline void std::swap(s3d::Mesh& a, s3d::Mesh& b) noexcept;

# include "detail/Mesh.ipp"
