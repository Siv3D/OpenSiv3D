
# include <Siv3D.hpp> // OpenSiv3D v0.4.1

//# include <DirectXMath.h>
//# define GLM_FORCE_DEPTH_ZERO_TO_ONE
//# define GLM_FORCE_LEFT_HANDED
//# define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
//# define GLM_FORCE_SSE42
//
//SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)
//SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4324)
//# include <glm/vec4.hpp>
//# include <glm/mat4x4.hpp>
//# include <glm/ext/matrix_transform.hpp>
//# include <glm/ext/matrix_clip_space.hpp>
//SIV3D_DISABLE_MSVC_WARNINGS_POP()
//SIV3D_DISABLE_MSVC_WARNINGS_POP()

//glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
//{
//	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
//	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
//	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
//	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
//	return Projection * View;
//}

//void Show(const DirectX::XMMATRIX& mat)
//{
//	for (auto i : step(4))
//	{
//		Print << 8_dp << Vec4(mat.r[i].m128_f32[0], mat.r[i].m128_f32[1], mat.r[i].m128_f32[2], mat.r[i].m128_f32[3]);
//	}
//}
//
//void Show(const glm::mat4& mat)
//{
//	for (auto i : step(4))
//	{
//		Print << 8_dp << Vec4(mat[i].x, mat[i].y, mat[i].z, mat[i].w);
//	}
//}

//namespace s3d
//{
//	struct Triangle3D
//	{
//		Vec3 p0, p1, p2;
//	};
//
//	struct Triangle3DA
//	{
//		using position_type = Vec2;
//
//		using value_type = position_type::value_type;
//
//		position_type p0, p1, p2;
//
//	SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4201)
//	
//	SIV3D_DISABLE_MSVC_WARNINGS_POP()
//
//	};
//
//	using DXMat4x4 = DirectX::XMMATRIX;
//	using DXVec4 = DirectX::XMVECTOR;
//
//	class BasicCamera3D
//	{
//	protected:
//
//		Vec3 m_eye = Vec3(0, 4, 0);
//
//		Vec3 m_lookAt = Vec3(0, 0, 0);
//
//		double m_fov = 45_deg;
//
//		double m_aspect = 1.0;
//
//	public:
//
//		BasicCamera3D() = default;
//
//		BasicCamera3D(const Vec3& eye, const Vec3& lookAt, double fov, double aspect) noexcept
//			: m_eye(eye)
//			, m_lookAt(lookAt)
//			, m_fov(fov)
//			, m_aspect(aspect) {}
//
//		virtual ~BasicCamera3D() = default;
//
//		void setEye(const Vec3& eye) noexcept
//		{
//			m_eye = eye;
//		}
//
//		void setLookAt(const Vec3& lookAt) noexcept
//		{
//			m_lookAt = lookAt;
//		}
//
//		[[nodiscard]] DXMat4x4 getDXMat4x4() const
//		{
//			constexpr float nearClip = 0.1f;
//			constexpr float farClip = 1000000.0f;
//
//			const DXVec4 eye{ static_cast<float>(m_eye.x), static_cast<float>(m_eye.y), static_cast<float>(m_eye.z), 0.0f };
//			const DXVec4 lookAt{ static_cast<float>(m_lookAt.x), static_cast<float>(m_lookAt.y), static_cast<float>(m_lookAt.z), 0.0f };
//			const DXVec4 up{ 0.0f, 1.0f, 0.0f, 0.0f };
//
//			const DirectX::XMMATRIX dxProj = DirectX::XMMatrixPerspectiveFovLH(static_cast<float>(m_fov), static_cast<float>(m_aspect), nearClip, farClip);
//			const DirectX::XMMATRIX dxView = DirectX::XMMatrixLookAtLH(eye, lookAt, up);
//			return DirectX::XMMatrixMultiply(dxView, dxProj);
//		}
//
//		[[nodiscard]] GLMat4x4 getGLMat4x4() const
//		{
//			constexpr float nearClip = 0.1f;
//			constexpr float farClip = 1000000.0f;
//
//			const glm::vec3 eye(m_eye.x, m_eye.y, m_eye.z);
//			const glm::vec3 lookAt(m_lookAt.x, m_lookAt.y, m_lookAt.z);
//			const glm::vec3 up(0.0f, 1.0f, 0.0f);
//
//			const GLMat4x4 glProj = glm::perspective(static_cast<float>(m_fov), static_cast<float>(m_aspect), nearClip, farClip);
//			const GLMat4x4 glView = glm::lookAtLH(eye, lookAt, up);
//			return glProj * glView;
//		}
//	};
//
//	Vec3 ToScreenPos(const Vec3& worldPos, const DirectX::XMMATRIX& vp)
//	{
//		const DirectX::XMVECTOR pos{ static_cast<float>(worldPos.x), static_cast<float>(worldPos.y), static_cast<float>(worldPos.z), 0.0f };
//		const DirectX::XMVECTOR out = DirectX::XMVector3TransformCoord(pos, vp);
//		const Vec2 resolution = Scene::Size();
//
//		Vec3 v(out.m128_f32[0], out.m128_f32[1], out.m128_f32[2]);
//		v.x += 1.0;
//		v.y += 1.0;
//		v.x *= 0.5 * resolution.x;
//		v.y *= 0.5;
//		v.y = 1.0 - v.y;
//		v.y *= resolution.y;
//
//		return v;
//	}
//
//	Vec3 ToScreenPos(const Vec3& worldPos, const glm::mat4x4& vp)
//	{
//		const glm::vec4 pos{ worldPos.x, worldPos.y, worldPos.z, 1.0f };
//		glm::vec4 transformed = vp * pos;
//		transformed.x /= transformed.w;
//		transformed.y /= transformed.w;
//		transformed.z /= transformed.w;
//		const Vec2 resolution = Scene::Size();
//
//		Vec3 v(transformed.x, transformed.y, transformed.z);
//		v.x += 1.0;
//		v.y += 1.0;
//		v.x *= 0.5 * resolution.x;
//		v.y *= 0.5;
//		v.y = 1.0 - v.y;
//		v.y *= resolution.y;
//
//		return v;
//	}
//
//	void Draw3D(const Triangle3D& triangle, const DirectX::XMMATRIX& vp, const ColorF& color)
//	{
//		const Vec3 t0 = ToScreenPos(triangle.p0, vp);
//		const Vec3 t1 = ToScreenPos(triangle.p1, vp);
//		const Vec3 t2 = ToScreenPos(triangle.p2, vp);
//		Triangle(t0.xy(), t1.xy(), t2.xy()).draw(color);
//	}
//
//	void Draw3D(const Triangle3D& triangle, const glm::mat4x4& vp, const ColorF& color)
//	{
//		const Vec3 t0 = ToScreenPos(triangle.p0, vp);
//		const Vec3 t1 = ToScreenPos(triangle.p1, vp);
//		const Vec3 t2 = ToScreenPos(triangle.p2, vp);
//		Triangle(t0.xy(), t1.xy(), t2.xy()).draw(color);
//	}
//}

void Main()
{
	const SIMD_Float4 ev(0.1f, 0.2f, 0.3f, 0.4f);

	SIMD_Float4 ev2(0.1f, 0.2f, 0.3f, 0.4f);
	Print << ev2;
	ev2.setX(1.1f);
	Print << ev2;
	ev2.setY(2.2f);
	Print << ev2;
	ev2.setZ(3.3f);
	Print << ev2;
	ev2.setW(4.4f);
	Print << ev2;

	Print << U"---";

	Print << Float4(ev.getX(), ev.getY(), ev.getZ(), ev.getW());

	Print << Float4(ev.elem(0), ev.elem(1), ev.elem(2), ev.elem(3));

	Print << Parse<SIMD_Float4>(U"(0.1, 0.2, 0.3, 0.4)");

	Print << SIMD_Float4(0.1f, 0.2f, 0.3f, 0.4f);

	Print << SIMD_Float4(0.1234f);

	SIMD_Float4 f0(0.1f, Random(0.2f), Random(0.2f), Random(0.2f));

	Print << f0;

	Print << (f0 + f0 + f0);

	Print << U"---";

	Print << ev.fastReciprocal();

	Print << ev.reciprocal();

	Print << ev.xy();

	Print << ev.xyz();

	while (System::Update())
	{
	
	}

	/*
	constexpr std::array<Vec3, 8> vertices =
	{
		Vec3(-1, 1, -1),
		Vec3(1, 1, -1),
		Vec3(-1, -1, -1),
		Vec3(1, -1, -1),

		Vec3(1, 1, 1),
		Vec3(-1, 1, 1),
		Vec3(1, -1, 1),
		Vec3(-1, -1, 1),
	};

	constexpr std::array<uint32, 36> indices =
	{
		0, 1, 2, 2, 1, 3,
		5, 4, 0, 0, 4, 1,
		1, 4, 3, 3, 4, 6,
		5, 0, 7, 7, 0, 2,
		4, 5, 6, 6, 5, 7,
		2, 3, 7, 7, 3, 6,
	};

	Window::Resize(1280, 720);

	const Vec3 eye(0, 4, -4);
	const Vec3 lookAt(0, 0, 0);
	const double fov = 45_deg;
	const double aspect = static_cast<double>(Scene::Width()) / Scene::Height();

	while (System::Update())
	{
		//ClearPrint();

		BasicCamera3D camera(Cylindrical(6, Scene::Time() * 30_deg, Sin(Scene::Time()) * 4), lookAt, fov, aspect);
		{
			ScopedRenderStates2D blend(RasterizerState::SolidCullBack);

			const glm::mat4x4 glVP = camera.getGLMat4x4();

			std::array<Vec3, vertices.size()> verticesTransformed;

			for (auto i : step(vertices.size()))
			{
				verticesTransformed[i] = vertices[i];
			}

			for (auto p : step(12))
			{
				const Triangle3D triangle0{ verticesTransformed[indices[p * 3 + 0]], verticesTransformed[indices[p * 3 + 1]], verticesTransformed[indices[p * 3 + 2]] };
				Draw3D(triangle0, glVP, HSV(p * 30, 0.9, 0.9));
			}
		}
	}
	*/
}
