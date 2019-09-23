
# include <Siv3D.hpp> // OpenSiv3D v0.4.1

//# define USE_DIRECTXMATH
//# define USE_GLM

# ifdef USE_DIRECTXMATH
# define _XM_SSE3_INTRINSICS_
# include <DirectXMath.h>
void Show(const DirectX::XMMATRIX& mat)
{
	for (auto i : step(4))
	{
		Print << 8_dp << Vec4(mat.r[i].m128_f32[0], mat.r[i].m128_f32[1], mat.r[i].m128_f32[2], mat.r[i].m128_f32[3]);
	}
}
# endif

# ifdef USE_GLM
//# define GLM_FORCE_DEPTH_ZERO_TO_ONE
//# define GLM_FORCE_LEFT_HANDED
# define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
# define GLM_FORCE_SSE42
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4324)
# include <glm/vec4.hpp>
# include <glm/mat4x4.hpp>
# include <glm/ext/matrix_transform.hpp>
# include <glm/ext/matrix_clip_space.hpp>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()
void Show(const glm::mat4& mat)
{
	for (auto i : step(4))
	{
		Print << 12_dp << Vec4(mat[i].x, mat[i].y, mat[i].z, mat[i].w);
	}
}
# endif

namespace s3d::experimental
{
	namespace Graphics3D
	{
		[[nodiscard]] Float3 SIV3D_VECTOR_CALL WorldToScreenPoint(SIMD_Float4 worldPos, Mat4x4 viewProjMat,
			const Float2& sceneSize = Graphics2D::GetRenderTargetSize())
		{
			Float3 v = SIMD::Vector3TransformCoord(worldPos, viewProjMat).xyz();
			v.x += 1.0f;
			v.y += 1.0f;
			v.x *= 0.5f * sceneSize.x;
			v.y *= 0.5f;
			v.y = 1.0f - v.y;
			v.y *= sceneSize.y;
			return v;
		}

		[[nodiscard]] Float3 SIV3D_VECTOR_CALL WorldToScreenPoint(const Vec3& worldPos, Mat4x4 viewProjMat,
			const Float2& sceneSize = Graphics2D::GetRenderTargetSize())
		{
			return WorldToScreenPoint(SIMD_Float4(worldPos, 0.0f), viewProjMat, sceneSize);
		}
	}

	struct alignas(16) SIMD_Triangle3D
	{
	SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			struct
			{
				SIMD_Float4 p0, p1, p2;
			};
			SIMD_Float4 vec[3];
		};

	SIV3D_DISABLE_MSVC_WARNINGS_POP()

		SIMD_Triangle3D() = default;

		SIMD_Triangle3D(const SIMD_Triangle3D&) = default;

		SIMD_Triangle3D& operator=(const SIMD_Triangle3D&) = default;

		SIMD_Triangle3D(SIMD_Triangle3D&&) = default;

		SIMD_Triangle3D& operator=(SIMD_Triangle3D&&) = default;

		constexpr SIMD_Triangle3D(SIMD_Float4 _p0, SIMD_Float4 _p1, SIMD_Float4 _p2) noexcept
			: p0(_p0)
			, p1(_p1)
			, p2(_p2) {}

		SIMD_Triangle3D(const Float3& _p0, const Float3& _p1, const Float3& _p2) noexcept
			: p0(_p0, 0.0f)
			, p1(_p1, 0.0f)
			, p2(_p2, 0.0f) {}

		void draw(const Mat4x4& vp, const ColorF& color) const
		{
			Float3 out[3];

			SIMD::Vector3TransformCoordStream(out, vec, 3, vp);

			const Float2 resolution = Graphics2D::GetRenderTargetSize();

			for (auto& v : out)
			{
				v.x += 1.0f;
				v.y += 1.0f;
				v.x *= 0.5f * resolution.x;
				v.y *= 0.5f;
				v.y = 1.0f - v.y;
				v.y *= resolution.y;
			}

			Triangle(out[0].xy(), out[1].xy(), out[2].xy()).draw(color);
		}
	};

	struct alignas(16) SIMD_Line3D
	{
	SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)

		union
		{
			struct
			{
				SIMD_Float4 begin, end;
			};
			SIMD_Float4 vec[2];
		};

	SIV3D_DISABLE_MSVC_WARNINGS_POP()

		SIMD_Line3D() = default;

		SIMD_Line3D(const SIMD_Line3D&) = default;

		SIMD_Line3D& operator=(const SIMD_Line3D&) = default;

		SIMD_Line3D(SIMD_Line3D&&) = default;

		SIMD_Line3D& operator=(SIMD_Line3D&&) = default;

		constexpr SIMD_Line3D(SIMD_Float4 _begin, SIMD_Float4 _end) noexcept
			: begin(_begin)
			, end(_end) {}

		SIMD_Line3D(const Float3& _begin, const Float3& _end) noexcept
			: begin(_begin, 0.0f)
			, end(_end, 0.0f) {}

		void draw(const Mat4x4& vp, const ColorF& color) const
		{
			Float3 out[2];

			SIMD::Vector3TransformCoordStream(out, vec, 2, vp);

			const Float2 resolution = Graphics2D::GetRenderTargetSize();

			for (auto& v : out)
			{
				v.x += 1.0f;
				v.y += 1.0f;
				v.x *= 0.5f * resolution.x;
				v.y *= 0.5f;
				v.y = 1.0f - v.y;
				v.y *= resolution.y;
			}

			Line(out[0].xy(), out[1].xy()).draw(2, color);
		}
	};

	struct AABB
	{
		Vec3 center;

		Vec3 size;

		AABB() = default;

		AABB(const AABB&) = default;

		AABB& operator=(const AABB&) = default;

		AABB(AABB&&) = default;

		AABB& operator=(AABB&&) = default;

		constexpr AABB(const Vec3& _center, const Vec3& _size) noexcept
			: center(_center)
			, size(_size) {}

		void draw(const Mat4x4& vp, const ColorF& color) const
		{
			constexpr size_t vertexCount = 8;
			const Float3 c = center;
			const Float3 s = size * 0.5;
			const std::array<Float3, vertexCount> vertices =
			{
				Float3(c.x - s.x, c.y + s.y, c.z - s.z),
				Float3(c.x + s.x, c.y + s.y, c.z - s.z),
				Float3(c.x - s.x, c.y - s.y, c.z - s.z),
				Float3(c.x + s.x, c.y - s.y, c.z - s.z),

				Float3(c.x + s.x, c.y + s.y, c.z + s.z),
				Float3(c.x - s.x, c.y + s.y, c.z + s.z),
				Float3(c.x + s.x, c.y - s.y, c.z + s.z),
				Float3(c.x - s.x, c.y - s.y, c.z + s.z),
			};
			static constexpr std::array<uint32, 36> indices =
			{
				0, 1, 2, 2, 1, 3,
				5, 4, 0, 0, 4, 1,
				1, 4, 3, 3, 4, 6,
				5, 0, 7, 7, 0, 2,
				4, 5, 6, 6, 5, 7,
				2, 3, 7, 7, 3, 6,
			};

			std::array<Float3, vertexCount> out;

			SIMD::Vector3TransformCoordStream(out.data(), vertices.data(), vertexCount, vp);

			const Float2 resolution = Graphics2D::GetRenderTargetSize();

			for (auto& v : out)
			{
				v.x += 1.0f;
				v.y += 1.0f;
				v.x *= 0.5f * resolution.x;
				v.y *= 0.5f;
				v.y = 1.0f - v.y;
				v.y *= resolution.y;
			}

			for (auto ii : step(indices.size() / 3))
			{
				const Float3 p0 = out[indices[ii * 3 + 0]];
				const Float3 p1 = out[indices[ii * 3 + 1]];
				const Float3 p2 = out[indices[ii * 3 + 2]];
				Triangle(p0.xy(), p1.xy(), p2.xy()).draw(color);
			}
		}
	};
}

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF(0.05, 0.3, 0.7));

	RenderTexture rt(100, 100, ColorF(0.0), TextureFormat::R32_Float);
	Grid<float> heightMap;
	Grid<Float3> positions;

	constexpr double fov = 45_deg;
	constexpr Vec3 focusPosition(50, 0, -50);
	Vec3 eyePositon(0, 100, 0);
	experimental::BasicCamera3D camera(Scene::Size(), fov, eyePositon, focusPosition);

	while (System::Update())
	{
		eyePositon = Cylindrical(Arg::r = 80, Arg::phi = Scene::Time() * 30_deg, Arg::y = 50) + Vec3(50, 0, -50);
		camera.setView(eyePositon, focusPosition);
		const Mat4x4 mat = camera.getMat4x4();

		rt.read(heightMap);
		{
			positions.resize(heightMap.size());

			for (auto p : step(heightMap.size()))
			{
				positions[p] = Float3(p.x, heightMap[p], -p.y);
			}
		}

		{
			ScopedRenderTarget2D target(rt);
			ScopedRenderStates2D blend(BlendState::Additive);

			if (MouseL.pressed())
			{
				Circle(Cursor::Pos(), 8).draw(ColorF(Scene::DeltaTime() * 24.0));
			}
		}

		if (positions)
		{
			ScopedRenderStates2D blend(RasterizerState::SolidCullBack);

			for (auto x : step(positions.width() - 1))
			{
				for (auto y : step(positions.height()))
				{
					const Float3 begin = positions[{x, y}];
					const Float3 end = positions[{x + 1, y}];
					const ColorF color = HSV(120 - (begin.y + end.y) * 3, 0.75, 0.7);
					experimental::SIMD_Line3D(begin, end).draw(mat, color);
				}
			}

			for (auto x : step(positions.width()))
			{
				for (auto y : step(positions.height() - 1))
				{
					const Float3 begin = positions[{x, y}];
					const Float3 end = positions[{x, y + 1}];
					const ColorF color = HSV(120 - (begin.y + end.y) * 3, 0.75, 0.7);
					experimental::SIMD_Line3D(begin, end).draw(mat, color);
				}
			}
		}

		rt.draw(ColorF(0.1));
	}
}
