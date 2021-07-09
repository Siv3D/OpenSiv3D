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
# include "Common.hpp"
# include "Array.hpp"
# include "Vertex3D.hpp"
# include "Mat4x4.hpp"
# include "ColorHSV.hpp"
# include "AssetHandle.hpp"

namespace s3d
{
	struct MeshData;
	struct Box;
	struct Sphere;
	class Texture;

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

		void draw(const ColorF& color = Palette::White) const;

		void draw(double x, double y, double z, const ColorF& color = Palette::White) const;

		void draw(const Vec3& pos, const ColorF& color = Palette::White) const;

		void draw(double x, double y, double z, const Quaternion& rotation, const ColorF& color = Palette::White) const;

		void draw(const Vec3& pos, const Quaternion& rotation, const ColorF& color = Palette::White) const;

		void draw(const Mat4x4& mat, const ColorF& color = Palette::White) const;



		void draw(const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(double x, double y, double z, const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(const Vec3& pos, const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(double x, double y, double z, const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(const Vec3& pos, const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		void draw(const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;


		void drawSubset(uint32 startTriangle, uint32 triangleCount, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const Quaternion& rotation, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Mat4x4& mat, const ColorF& color = Palette::White) const;



		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, double x, double y, double z, const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Vec3& pos, const Quaternion& rotation, const Texture& texture, const ColorF& color = Palette::White) const;

		void drawSubset(uint32 startTriangle, uint32 triangleCount, const Mat4x4& mat, const Texture& texture, const ColorF& color = Palette::White) const;


		void swap(Mesh& other) noexcept;
	};
}

template <>
inline void std::swap(s3d::Mesh& a, s3d::Mesh& b) noexcept;

# include "detail/Mesh.ipp"
