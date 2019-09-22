
# include <Siv3D.hpp> // OpenSiv3D v0.4.1
# include <DirectXMath.h>

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

void Show(const DirectX::XMMATRIX& mat)
{
	for (auto i : step(4))
	{
		Print << 8_dp << Vec4(mat.r[i].m128_f32[0], mat.r[i].m128_f32[1], mat.r[i].m128_f32[2], mat.r[i].m128_f32[3]);
	}
}
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

//struct alignas(16) SIMD_Line3D
//{
//	SIMD_Float4 begin;
//
//	SIMD_Float4 end;
//};
//
//	using DXMat4x4 = DirectX::XMMATRIX;
//	using DXVec4 = DirectX::XMVECTOR;
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

//	void Draw3D(const Triangle3D& triangle, const glm::mat4x4& vp, const ColorF& color)
//	{
//		const Vec3 t0 = ToScreenPos(triangle.p0, vp);
//		const Vec3 t1 = ToScreenPos(triangle.p1, vp);
//		const Vec3 t2 = ToScreenPos(triangle.p2, vp);
//		Triangle(t0.xy(), t1.xy(), t2.xy()).draw(color);
//	}
//}
using DXMat4x4 = DirectX::XMMATRIX;

namespace s3d
{
	struct alignas(16) Mat4x4
	{
		SIMD_Float4 r[4];

		Mat4x4() = default;

		Mat4x4(const Mat4x4&) = default;
		
		Mat4x4& operator=(const Mat4x4&) = default;

		Mat4x4(Mat4x4&&) = default;
		
		Mat4x4& operator=(Mat4x4&&) = default;

		constexpr Mat4x4(SIMD_Float4 r0, SIMD_Float4 r1, SIMD_Float4 r2, SIMD_Float4 r3) noexcept
			: r{ r0, r1, r2, r3 } {}

		Mat4x4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
		) noexcept
			: r{
				{ m00, m01, m02, m03 },
				{ m10, m11, m12, m13 },
				{ m20, m21, m22, m23 },
				{ m30, m31, m32, m33 }} {}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator +() const noexcept
		{
			return *this;
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator -() const noexcept
		{
			return{ -r[0], -r[1], -r[2], -r[3] };
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator +(Mat4x4 m) const noexcept
		{
			return{ r[0] + m.r[0], r[1] + m.r[1], r[2] + m.r[2], r[3] + m.r[3] };
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator -(Mat4x4 m) const noexcept
		{
			return{ r[0] - m.r[0], r[1] - m.r[1], r[2] - m.r[2], r[3] - m.r[3] };
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator *(float s) const noexcept
		{
			return{ r[0] * s, r[1] * s, r[2] * s, r[3] * s };
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator *(Mat4x4 m) const noexcept
		{
			//
			// https://github.com/microsoft/DirectXMath/blob/master/Inc/DirectXMathMatrix.inl
			//
			Mat4x4 mResult;

			// Use vW to hold the original row
			__m128 vW = r[0];
			__m128 vX = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
			__m128 vY = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 vZ = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
			vW = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
			// Perform the operation on the first row
			vX = _mm_mul_ps(vX, m.r[0]);
			vY = _mm_mul_ps(vY, m.r[1]);
			vZ = _mm_mul_ps(vZ, m.r[2]);
			vW = _mm_mul_ps(vW, m.r[3]);
			// Perform a binary add to reduce cumulative errors
			vX = _mm_add_ps(vX, vZ);
			vY = _mm_add_ps(vY, vW);
			vX = _mm_add_ps(vX, vY);
			mResult.r[0] = vX;

			vW = r[1];
			vX = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
			vY = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
			vZ = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
			vW = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
			vX = _mm_mul_ps(vX, m.r[0]);
			vY = _mm_mul_ps(vY, m.r[1]);
			vZ = _mm_mul_ps(vZ, m.r[2]);
			vW = _mm_mul_ps(vW, m.r[3]);
			vX = _mm_add_ps(vX, vZ);
			vY = _mm_add_ps(vY, vW);
			vX = _mm_add_ps(vX, vY);
			mResult.r[1] = vX;

			vW = r[2];
			vX = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
			vY = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
			vZ = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
			vW = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
			vX = _mm_mul_ps(vX, m.r[0]);
			vY = _mm_mul_ps(vY, m.r[1]);
			vZ = _mm_mul_ps(vZ, m.r[2]);
			vW = _mm_mul_ps(vW, m.r[3]);
			vX = _mm_add_ps(vX, vZ);
			vY = _mm_add_ps(vY, vW);
			vX = _mm_add_ps(vX, vY);
			mResult.r[2] = vX;

			vW = r[3];
			vX = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(0, 0, 0, 0));
			vY = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(1, 1, 1, 1));
			vZ = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(2, 2, 2, 2));
			vW = SIV3D_PERMUTE_PS(vW, _MM_SHUFFLE(3, 3, 3, 3));
			vX = _mm_mul_ps(vX, m.r[0]);
			vY = _mm_mul_ps(vY, m.r[1]);
			vZ = _mm_mul_ps(vZ, m.r[2]);
			vW = _mm_mul_ps(vW, m.r[3]);
			vX = _mm_add_ps(vX, vZ);
			vY = _mm_add_ps(vY, vW);
			vX = _mm_add_ps(vX, vY);
			mResult.r[3] = vX;

			return mResult;
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL operator /(float s) const noexcept
		{
			return{ r[0] / s, r[1] / s, r[2] / s, r[3] / s };
		}

		Mat4x4& SIV3D_VECTOR_CALL operator +=(Mat4x4 v) noexcept
		{
			r[0] += v.r[0];
			r[1] += v.r[1];
			r[2] += v.r[2];
			r[3] += v.r[3];
			return *this;
		}

		Mat4x4& SIV3D_VECTOR_CALL operator -=(Mat4x4 v) noexcept
		{
			r[0] -= v.r[0];
			r[1] -= v.r[1];
			r[2] -= v.r[2];
			r[3] -= v.r[3];
			return *this;
		}

		Mat4x4& SIV3D_VECTOR_CALL operator *=(float s) noexcept
		{
			r[0] *= s;
			r[1] *= s;
			r[2] *= s;
			r[3] *= s;
			return *this;
		}

		Mat4x4& SIV3D_VECTOR_CALL operator *=(Mat4x4 m) noexcept
		{
			*this = (*this * m);
			return *this;
		}

		Mat4x4& SIV3D_VECTOR_CALL operator /=(float s) noexcept
		{
			r[0] /= s;
			r[1] /= s;
			r[2] /= s;
			r[3] /= s;
			return *this;
		}

		static Mat4x4 Identity() noexcept
		{
			return Mat4x4{
				SIMD::constants::m128_MIdentityR0,
				SIMD::constants::m128_MIdentityR1,
				SIMD::constants::m128_MIdentityR2,
				SIMD::constants::m128_MIdentityR3
			};
		}
	};

	[[nodiscard]] inline Mat4x4 SIV3D_VECTOR_CALL operator *(float s, Mat4x4 m) noexcept
	{
		return{ s * m.r[0], s * m.r[1], s * m.r[2], s * m.r[3] };
	}

	void Formatter(FormatData& formatData, const Mat4x4& value)
	{
		formatData.string.push_back(U'(');
		Formatter(formatData, value.r[0]);
		formatData.string.append(U",\n "sv);
		Formatter(formatData, value.r[1]);
		formatData.string.append(U",\n "sv);
		Formatter(formatData, value.r[2]);
		formatData.string.append(U",\n "sv);
		Formatter(formatData, value.r[3]);
		formatData.string.push_back(L')');
	}

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Mat4x4& value)
	{
		return output << CharType('(')
			<< value.r[0] << CharType(',') << CharType('\n') << CharType(' ')
			<< value.r[1] << CharType(',') << CharType('\n') << CharType(' ')
			<< value.r[2] << CharType(',') << CharType('\n') << CharType(' ')
			<< value.r[3] << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Mat4x4& value)
	{
		CharType unused;
		input >> unused
			>> value.r[0] >> unused
			>> value.r[1] >> unused
			>> value.r[2] >> unused
			>> value.r[3] >> unused;
		return input;
	}

	namespace SIMD
	{
		SIMD_Float4 SIV3D_VECTOR_CALL Vector3TransformCoord(SIMD_Float4 v, Mat4x4 m)
		{
			__m128 Z = SplatZ(v);
			__m128 Y = SplatY(v);
			__m128 X = SplatX(v);

			__m128 Result = MultiplyAdd(Z, m.r[2], m.r[3]);
			Result = MultiplyAdd(Y, m.r[1], Result);
			Result = MultiplyAdd(X, m.r[0], Result);

			__m128 W = SplatW(Result);
			return Divide(Result, W);
		}
	}

	Mat4x4 SIV3D_VECTOR_CALL PerspectiveFovLH(float fov, float aspectRatio, float nearClip, float farClip)
	{
		assert(0.0f < nearClip && 0.0f < farClip);
		assert(0.00001f <= aspect);

		const float sinFov = std::sin(0.5f * fov);
		const float cosFov = std::cos(0.5f * fov);

		const float height = cosFov / sinFov;
		const float width = height / aspectRatio;
		const float fRange = farClip / (farClip - nearClip);

		Mat4x4 m;
		m.r[0] = SIMD_Float4(width, 0.0f, 0.0f, 0.0f);
		m.r[1] = SIMD_Float4(0.0f, height, 0.0f, 0.0f);
		m.r[2] = SIMD_Float4(0.0f, 0.0f, fRange, 1.0f);
		m.r[3] = SIMD_Float4(0.0f, 0.0f, -fRange * nearClip, 0.0f);

		return m;
	}

	Mat4x4 SIV3D_VECTOR_CALL Transpose(Mat4x4 m)
	{
		// x.x,x.y,y.x,y.y
		__m128 vTemp1 = _mm_shuffle_ps(m.r[0], m.r[1], _MM_SHUFFLE(1, 0, 1, 0));
		// x.z,x.w,y.z,y.w
		__m128 vTemp3 = _mm_shuffle_ps(m.r[0], m.r[1], _MM_SHUFFLE(3, 2, 3, 2));
		// z.x,z.y,w.x,w.y
		__m128 vTemp2 = _mm_shuffle_ps(m.r[2], m.r[3], _MM_SHUFFLE(1, 0, 1, 0));
		// z.z,z.w,w.z,w.w
		__m128 vTemp4 = _mm_shuffle_ps(m.r[2], m.r[3], _MM_SHUFFLE(3, 2, 3, 2));

		Mat4x4 mResult;

		// x.x,y.x,z.x,w.x
		mResult.r[0] = _mm_shuffle_ps(vTemp1, vTemp2, _MM_SHUFFLE(2, 0, 2, 0));
		// x.y,y.y,z.y,w.y
		mResult.r[1] = _mm_shuffle_ps(vTemp1, vTemp2, _MM_SHUFFLE(3, 1, 3, 1));
		// x.z,y.z,z.z,w.z
		mResult.r[2] = _mm_shuffle_ps(vTemp3, vTemp4, _MM_SHUFFLE(2, 0, 2, 0));
		// x.w,y.w,z.w,w.w
		mResult.r[3] = _mm_shuffle_ps(vTemp3, vTemp4, _MM_SHUFFLE(3, 1, 3, 1));

		return mResult;
	}

	Mat4x4 SIV3D_VECTOR_CALL LookAtLH(SIMD_Float4 eyePosition, SIMD_Float4 focusPosition, SIMD_Float4 upDirection)
	{
		const SIMD_Float4 eyeDirection = focusPosition - eyePosition;

		//assert(!XMVector3Equal(EyeDirection, XMVectorZero()));
		//assert(!XMVector3IsInfinite(EyeDirection));
		//assert(!XMVector3Equal(UpDirection, XMVectorZero()));
		//assert(!XMVector3IsInfinite(UpDirection));

		const SIMD_Float4 R2 = SIMD::Vector3Normalize(eyeDirection);

		SIMD_Float4 R0 = SIMD::Vector3Cross(upDirection, R2);
		R0 = SIMD::Vector3Normalize(R0);

		SIMD_Float4 R1 = SIMD::Vector3Cross(R2, R0);

		SIMD_Float4 negEyePosition = -eyePosition;

		SIMD_Float4 D0 = SIMD::Vector3Dot(R0, negEyePosition);
		SIMD_Float4 D1 = SIMD::Vector3Dot(R1, negEyePosition);
		SIMD_Float4 D2 = SIMD::Vector3Dot(R2, negEyePosition);

		Mat4x4 m;
		m.r[0] = SIMD::Select(D0, R0, SIMD::constants::m128_Select1110.vec);
		m.r[1] = SIMD::Select(D1, R1, SIMD::constants::m128_Select1110.vec);
		m.r[2] = SIMD::Select(D2, R2, SIMD::constants::m128_Select1110.vec);
		m.r[3] = SIMD::constants::m128_MIdentityR3;

		return Transpose(m);
	}

	using DXMat4x4 = DirectX::XMMATRIX;
	using DXVec4 = DirectX::XMVECTOR;

	class BasicCamera3D
	{
	protected:

		Vec3 m_eyePosition = Vec3(0, 4, -4);

		Vec3 m_focusPosition = Vec3(0, 0, 0);

		Vec3 m_upDirection = Vec3(0, 1, 0);

		double m_fov = 45_deg;

		double m_aspectRatio = 1.0;

		double m_nearClip = 0.1;

		double m_farClip = 1000000.0;

	public:

		BasicCamera3D() = default;

		BasicCamera3D(const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection, double fov, double aspectRatio) noexcept
			: m_eyePosition(eyePosition)
			, m_focusPosition(focusPosition)
			, m_upDirection(upDirection)
			, m_fov(fov)
			, m_aspectRatio(aspectRatio) {}

		virtual ~BasicCamera3D() = default;

		void setEyePosition(const Vec3& eyePosition) noexcept
		{
			m_eyePosition = eyePosition;
		}

		void setFocusPosition(const Vec3& focusPosition) noexcept
		{
			m_focusPosition = focusPosition;
		}

		[[nodiscard]] DXMat4x4 SIV3D_VECTOR_CALL getDXMat4x4() const
		{
			const float nearClip = static_cast<float>(m_nearClip);
			const float farClip = static_cast<float>(m_farClip);

			const DXVec4 eye{ static_cast<float>(m_eyePosition.x), static_cast<float>(m_eyePosition.y), static_cast<float>(m_eyePosition.z), 0.0f };
			const DXVec4 lookAt{ static_cast<float>(m_focusPosition.x), static_cast<float>(m_focusPosition.y), static_cast<float>(m_focusPosition.z), 0.0f };
			const DXVec4 up{ static_cast<float>(m_upDirection.x), static_cast<float>(m_upDirection.y), static_cast<float>(m_upDirection.z), 0.0f };

			const DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(static_cast<float>(m_fov), static_cast<float>(m_aspectRatio), nearClip, farClip);
			const DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(eye, lookAt, up);

			return DirectX::XMMatrixMultiply(view, proj);
		}

		[[nodiscard]] Mat4x4 SIV3D_VECTOR_CALL getMat4x4() const
		{
			const float nearClip = static_cast<float>(m_nearClip);
			const float farClip = static_cast<float>(m_farClip);

			const SIMD_Float4 eyePosition{ m_eyePosition, 0.0f };
			const SIMD_Float4 focusPosition{ m_focusPosition, 0.0f };
			const SIMD_Float4 upDirection{ m_upDirection, 0.0f };

			const Mat4x4 proj = PerspectiveFovLH(static_cast<float>(m_fov), static_cast<float>(m_aspectRatio), nearClip, farClip);
			const Mat4x4 view = LookAtLH(eyePosition, focusPosition, upDirection);

			return view * proj;
		}

		//[[nodiscard]] GLMat4x4 getGLMat4x4() const
		//{
		//	constexpr float nearClip = 0.1f;
		//	constexpr float farClip = 1000000.0f;

		//	const glm::vec3 eye(m_eye.x, m_eye.y, m_eye.z);
		//	const glm::vec3 lookAt(m_lookAt.x, m_lookAt.y, m_lookAt.z);
		//	const glm::vec3 up(0.0f, 1.0f, 0.0f);

		//	const GLMat4x4 glProj = glm::perspective(static_cast<float>(m_fov), static_cast<float>(m_aspect), nearClip, farClip);
		//	const GLMat4x4 glView = glm::lookAtLH(eye, lookAt, up);
		//	return glProj * glView;
		//}
	};

	Vec3 ToScreenPos(const Vec3& worldPos, const DirectX::XMMATRIX& vp)
	{
		const DirectX::XMVECTOR pos{ static_cast<float>(worldPos.x), static_cast<float>(worldPos.y), static_cast<float>(worldPos.z), 0.0f };
		const DirectX::XMVECTOR out = DirectX::XMVector3TransformCoord(pos, vp);
		const Vec2 resolution = Scene::Size();

		Vec3 v(out.m128_f32[0], out.m128_f32[1], out.m128_f32[2]);
		v.x += 1.0;
		v.y += 1.0;
		v.x *= 0.5 * resolution.x;
		v.y *= 0.5;
		v.y = 1.0 - v.y;
		v.y *= resolution.y;

		return v;
	}

	Vec3 SIV3D_VECTOR_CALL ToScreenPos(SIMD_Float4 worldPos, Mat4x4 viewProjMat)
	{
		const DirectX::XMVECTOR out = SIMD::Vector3TransformCoord(worldPos, viewProjMat);
		const Vec2 resolution = Scene::Size();

		Vec3 v(out.m128_f32[0], out.m128_f32[1], out.m128_f32[2]);
		v.x += 1.0;
		v.y += 1.0;
		v.x *= 0.5 * resolution.x;
		v.y *= 0.5;
		v.y = 1.0 - v.y;
		v.y *= resolution.y;

		return v;
	}

	struct Triangle3D
	{
		Vec3 p0, p1, p2;
	};

	struct alignas(16) SIMD_Triangle3D
	{
		SIMD_Float4 p0, p1, p2;
	};

	void Draw3D(const Triangle3D& triangle, const DirectX::XMMATRIX& vp, const ColorF& color)
	{
		const Vec3 t0 = ToScreenPos(triangle.p0, vp);
		const Vec3 t1 = ToScreenPos(triangle.p1, vp);
		const Vec3 t2 = ToScreenPos(triangle.p2, vp);
		Triangle(t0.xy(), t1.xy(), t2.xy()).draw(color);
	}

	void Draw3D(const SIMD_Triangle3D& triangle, const Mat4x4& vp, const ColorF& color)
	{
		const Vec3 t0 = ToScreenPos(triangle.p0, vp);
		const Vec3 t1 = ToScreenPos(triangle.p1, vp);
		const Vec3 t2 = ToScreenPos(triangle.p2, vp);
		Triangle(t0.xy(), t1.xy(), t2.xy()).draw(color);
	}
}

void Main()
{
	Mat4x4 m = Mat4x4::Identity();
	//Print << m;
	//Print << Parse<Mat4x4>(Format(Mat4x4::Identity()));

	BasicCamera3D camera;
	Show(camera.getDXMat4x4());

	Print << 8_dp << camera.getMat4x4();
	//Show(camera.getDXMat4x4());

	/*
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
	*/


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

		BasicCamera3D camera(Cylindrical(6, Scene::Time() * 30_deg, Sin(Scene::Time()) * 4), lookAt, Vec3(0, 1, 0), fov, aspect);
		{
			ScopedRenderStates2D blend(RasterizerState::SolidCullBack);

			const auto viewProjMat = camera.getMat4x4();

			std::array<Vec3, vertices.size()> verticesTransformed;

			for (auto i : step(vertices.size()))
			{
				verticesTransformed[i] = vertices[i];
			}

			/*
			for (auto p : step(12))
			{
				const Triangle3D triangle0{ verticesTransformed[indices[p * 3 + 0]], verticesTransformed[indices[p * 3 + 1]], verticesTransformed[indices[p * 3 + 2]] };
				Draw3D(triangle0, viewProjMat, HSV(p * 30, 0.9, 0.9));
			}
			*/

			for (auto p : step(12))
			{
				const SIMD_Float4 p0(verticesTransformed[indices[p * 3 + 0]], 0.0f);
				const SIMD_Float4 p1(verticesTransformed[indices[p * 3 + 1]], 0.0f);
				const SIMD_Float4 p2(verticesTransformed[indices[p * 3 + 2]], 0.0f);

				const SIMD_Triangle3D triangle0{ p0, p1, p2};
				Draw3D(triangle0, viewProjMat, HSV(p * 30, 0.9, 0.9));
			}
		}
	}
}
