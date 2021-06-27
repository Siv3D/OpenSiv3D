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
# include <Siv3D/AABB.hpp>
# include <Siv3D/Sphere.hpp>
# include <Siv3D/FastMath.hpp>
# include <Siv3D/Math.hpp>
# include <Siv3D/Mesh/IMesh.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Renderer3D/IRenderer3D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>

namespace s3d
{
	namespace detail
	{
		const Array<Vertex3D::IndexType> BoxIndices =
		{
			0, 1, 2, 2, 1, 3,
			4, 5, 6, 6, 5, 7,
			8, 9, 10, 10, 9, 11,
			12, 13, 14, 14, 13, 15,
			16, 17, 18, 18, 17, 19,
			20, 21, 22, 22, 21, 23
		};

		[[nodiscard]]
		static Array<Vertex3D> GenerateAABBVertices(const AABB& aabb)
		{
			const Float3 s = aabb.size * 0.5;

			Array<Vertex3D> vertices =
			{
				{ { -s.x, s.y, -s.z }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } },
				{ { s.x, s.y, -s.z }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } },
				{ { -s.x, -s.y, -s.z }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } },
				{ { s.x, -s.y, -s.z }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } },

				{ { s.x, s.y, -s.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
				{ { s.x, s.y, s.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
				{ { s.x, -s.y, -s.z }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
				{ { s.x, -s.y, s.z }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },

				{ { s.x, s.y, s.z }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
				{ { -s.x, s.y, s.z }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } },
				{ { s.x, -s.y, s.z }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } },
				{ { -s.x, -s.y, s.z }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },

				{ { -s.x, s.y, s.z }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
				{ { s.x, s.y, s.z }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
				{ { -s.x, s.y, -s.z }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
				{ { s.x, s.y, -s.z }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },

				{ { -s.x, s.y, s.z }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
				{ { -s.x, s.y, -s.z }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
				{ { -s.x, -s.y, s.z }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
				{ { -s.x, -s.y, -s.z }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },

				{ { -s.x, -s.y, -s.z }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } },
				{ { s.x, -s.y, -s.z }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } },
				{ { -s.x, -s.y, s.z }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },
				{ { s.x, -s.y, s.z }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } },
			};

			if (not aabb.center.isZero())
			{
				const Float3 offset = aabb.center;

				for (auto& vertex : vertices)
				{
					vertex.pos += offset;
				}
			}

			return vertices;
		}

		[[nodiscard]]
		static Array<Vertex3D> GenerateSphereVertices(const Sphere& sphere, const uint32 _quality)
		{
			const uint32 quality = Clamp(_quality, 4u, 100u);
			const uint32 HDIV = quality; // 半球分割数
			const uint32 DIV = HDIV * 2; // 全球分割数(偶数)
			const uint32 DIVPR = DIV + 1; // 一周あたりの頂点数
			const uint32 vsize = (DIV - 1) * DIVPR;
			const uint32 isize = DIV * 6 * HDIV;

			Array<Vertex3D> vertices(vsize);

			const float deltaU = 1.0f / DIV;
			const float deltaV = 1.0f / HDIV;
			const float deltaRU = Math::ToRadians(180.0f / HDIV);
			const float deltaRB = Math::ToRadians(360.0f / DIV);
			const float rf = static_cast<float>(sphere.r);

			for (uint32 h = 0; h <= HDIV; ++h)
			{
				for (uint32 i = 0; i < DIVPR; ++i)
				{
					const float rU = (deltaRU * h);
					const float rB = (deltaRB * i);
					const auto [su, cu] = FastMath::SinCos(rU);
					const auto [sb, cb] = FastMath::SinCos(rB);

					const float x = su * cb;
					const float y = cu;
					const float z = su * sb;

					auto& vtx = vertices[(DIVPR * h) + i];
					vtx.pos.set(x * rf, y * rf, z * rf);
					vtx.normal.set(x, y, z);
					vtx.tex.set(deltaU * i, deltaV * h);
				}
			}

			if (not sphere.center.isZero())
			{
				const Float3 offset = sphere.center;

				for (auto& vertex : vertices)
				{
					vertex.pos += offset;
				}
			}

			return vertices;
		}

		[[nodiscard]]
		static Array<Vertex3D::IndexType> GenerateSphereIndices(const uint32 _quality)
		{
			const uint32 quality = Clamp(_quality, 4u, 100u);
			const uint32 HDIV = quality; // 半球分割数
			const uint32 DIV = HDIV * 2; // 全球分割数(偶数)
			const uint32 DIVPR = DIV + 1; // 一周あたりの頂点数
			[[maybe_unused]] const uint32 vsize = (DIV - 1) * DIVPR;
			const uint32 isize = DIV * 6 * HDIV;

			Array<uint32> indices(isize);

			for (uint32 h = 0; h < HDIV; ++h)
			{
				for (uint32 c = 0; c < DIV; ++c)
				{
					const uint32 offset = (6 * DIV) * h + c * 6;
					const uint32 idOffset = DIVPR * h + c;

					indices[offset + 0] = idOffset + 0;
					indices[offset + 1] = idOffset + 1;
					indices[offset + 2] = idOffset + DIVPR;
					indices[offset + 3] = idOffset + DIVPR + 1;
					indices[offset + 4] = idOffset + DIVPR;
					indices[offset + 5] = idOffset + 1;

					assert(offset + 5u < isize);
					assert(DIVPR * h + c + DIVPR + 1 < vsize);
				}
			}

			return indices;
		}
	}

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

	Mesh::Mesh(const AABB& aabb)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Mesh)->create(detail::GenerateAABBVertices(aabb), detail::BoxIndices)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Mesh::Mesh(const Sphere& sphere, const uint32 quality)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Mesh)->create(detail::GenerateSphereVertices(sphere, quality), detail::GenerateSphereIndices(quality))) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Mesh::~Mesh() {}

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

	void Mesh::draw(const Mat4x4& mat, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer3D)->addMesh(*this, mat, color.toFloat4());
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

	void Mesh::draw(const Mat4x4& mat, const Texture& texture, const ColorF& color) const
	{
		SIV3D_ENGINE(Renderer3D)->addTexturedMesh(*this, texture, mat, color.toFloat4());
	}
}
