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

# include <Siv3D/Script.hpp>
# include <Siv3D/Interpolation.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	using namespace AngelScript;

	static double DoubleLerp(double v1, double v2, double f) noexcept
	{
		return Math::Lerp(v1, v2, f);
	}

	static double MathSmoothDampDN(double from, double to, double& velocity, double smoothTime, const uint8&, double deltaTime)
	{
		return Math::SmoothDamp(from, to, velocity, smoothTime, unspecified, deltaTime);
	}

	static double MathSmoothDampDD(double from, double to, double& velocity, double smoothTime, double maxSpeed, double deltaTime)
	{
		return Math::SmoothDamp(from, to, velocity, smoothTime, maxSpeed, deltaTime);
	}

	static auto MathSmoothDampNVec2(const Vec2& from, const Vec2& to, Vec2& velocity, double smoothTime, const uint8&, double deltaTime)
	{
		return Math::SmoothDamp(from, to, velocity, smoothTime, unspecified, deltaTime);
	}

	static auto MathSmoothDampVec2(const Vec2& from, const Vec2& to, Vec2& velocity, double smoothTime, double maxSpeed, double deltaTime)
	{
		return Math::SmoothDamp(from, to, velocity, smoothTime, maxSpeed, deltaTime);
	}

	static auto MathSmoothDampNVec3(const Vec3& from, const Vec3& to, Vec3& velocity, double smoothTime, const uint8&, double deltaTime)
	{
		return Math::SmoothDamp(from, to, velocity, smoothTime, unspecified, deltaTime);
	}

	static auto MathSmoothDampVec3(const Vec3& from, const Vec3& to, Vec3& velocity, double smoothTime, double maxSpeed, double deltaTime)
	{
		return Math::SmoothDamp(from, to, velocity, smoothTime, maxSpeed, deltaTime);
	}

	static auto MathSmoothDampNVec4(const Vec4& from, const Vec4& to, Vec4& velocity, double smoothTime, const uint8&, double deltaTime)
	{
		return Math::SmoothDamp(from, to, velocity, smoothTime, unspecified, deltaTime);
	}

	static auto MathSmoothDampVec4(const Vec4& from, const Vec4& to, Vec4& velocity, double smoothTime, double maxSpeed, double deltaTime)
	{
		return Math::SmoothDamp(from, to, velocity, smoothTime, maxSpeed, deltaTime);
	}

	void RegisterInterpolation(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;
		r = engine->SetDefaultNamespace("Math"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("double Lerp(double, double, double)", asFUNCTION(DoubleLerp), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 Lerp(const Vec2& in, const Vec2& in, double)", asFUNCTIONPR(Math::Lerp, (const Vec2&, const Vec2&, double), Vec2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 Lerp(const Vec3& in, const Vec3& in, double)", asFUNCTIONPR(Math::Lerp, (const Vec3&, const Vec3&, double), Vec3), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec4 Lerp(const Vec4& in, const Vec4& in, double)", asFUNCTIONPR(Math::Lerp, (const Vec4&, const Vec4&, double), Vec4), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Color Lerp(const Color& in, const Color& in, double)", asFUNCTIONPR(Math::Lerp, (const Color&, const Color&, double), Color), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("ColorF Lerp(const ColorF& in, const ColorF& in, double)", asFUNCTIONPR(Math::Lerp, (const ColorF&, const ColorF&, double), ColorF), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("HSV Lerp(const HSV& in, const HSV& in, double)", asFUNCTIONPR(Math::Lerp, (const HSV&, const HSV&, double), HSV), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Line Lerp(const Line& in, const Line& in, double)", asFUNCTIONPR(Math::Lerp, (const Line&, const Line&, double), Line), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("RectF Lerp(const RectF& in, const RectF& in, double)", asFUNCTIONPR(Math::Lerp, (const RectF&, const RectF&, double), RectF), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Circle Lerp(const Circle& in, const Circle& in, double)", asFUNCTIONPR(Math::Lerp, (const Circle&, const Circle&, double), Circle), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Ellipse Lerp(const Ellipse& in, const Ellipse& in, double)", asFUNCTIONPR(Math::Lerp, (const Ellipse&, const Ellipse&, double), Ellipse), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Triangle Lerp(const Triangle& in, const Triangle& in, double)", asFUNCTIONPR(Math::Lerp, (const Triangle&, const Triangle&, double), Triangle), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Quad Lerp(const Quad& in, const Quad& in, double)", asFUNCTIONPR(Math::Lerp, (const Quad&, const Quad&, double), Quad), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("double InvLerp(double, double, double)", asFUNCTION(Math::InvLerp), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("double Damp(double value, double a, double b, const double& in, const double& in)", asFUNCTIONPR(Math::Map, (double, double, double, const double&, const double&), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 Damp(double value, double a, double b, const Vec2& in, const Vec2& in)", asFUNCTIONPR(Math::Map, (double, double, double, const Vec2&, const Vec2&), Vec2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 Damp(double value, double a, double b, const Vec3& in, const Vec3& in)", asFUNCTIONPR(Math::Map, (double, double, double, const Vec3&, const Vec3&), Vec3), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec4 Damp(double value, double a, double b, const Vec4& in, const Vec4& in)", asFUNCTIONPR(Math::Map, (double, double, double, const Vec4&, const Vec4&), Vec4), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("double LerpAngle(double, double, double)", asFUNCTIONPR(Math::LerpAngle, (double, double, double), double), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("double Eerp(double, double, double)", asFUNCTION(Math::Eerp), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("double Damp(double, double, double, double)", asFUNCTIONPR(Math::Damp, (double, double, double, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 Damp(const Vec2& in, const Vec2& in, double, double)", asFUNCTIONPR(Math::Damp, (const Vec2&, const Vec2&, double, double), Vec2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 Damp(const Vec3& in, const Vec3& in, double, double)", asFUNCTIONPR(Math::Damp, (const Vec3&, const Vec3&, double, double), Vec3), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec4 Damp(const Vec4& in, const Vec4& in, double, double)", asFUNCTIONPR(Math::Damp, (const Vec4&, const Vec4&, double, double), Vec4), asCALL_CDECL); assert(r >= 0);


			r = engine->RegisterGlobalFunction("double SmoothDamp(double from, double to, double& inout velocity, double smoothTime, None_t = unspecified, double deltaTime = Scene::DeltaTime())", asFUNCTION(MathSmoothDampDN), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double SmoothDamp(double from, double to, double& inout velocity, double smoothTime, double maxSpeed, double deltaTime = Scene::DeltaTime())", asFUNCTION(MathSmoothDampDD), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("Vec2 SmoothDamp(const Vec2& in from, const Vec2& in to, Vec2& inout velocity, double smoothTime, None_t = unspecified, double deltaTime = Scene::DeltaTime())", asFUNCTION(MathSmoothDampNVec2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec2 SmoothDamp(const Vec2& in from, const Vec2& in to, Vec2& inout velocity, double smoothTime, double maxSpeed, double deltaTime = Scene::DeltaTime())", asFUNCTION(MathSmoothDampVec2), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("Vec3 SmoothDamp(const Vec3& in from, const Vec3& in to, Vec3& inout velocity, double smoothTime, None_t = unspecified, double deltaTime = Scene::DeltaTime())", asFUNCTION(MathSmoothDampNVec3), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec3 SmoothDamp(const Vec3& in from, const Vec3& in to, Vec3& inout velocity, double smoothTime, double maxSpeed, double deltaTime = Scene::DeltaTime())", asFUNCTION(MathSmoothDampVec3), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("Vec4 SmoothDamp(const Vec4& in from, const Vec4& in to, Vec4& inout velocity, double smoothTime, None_t = unspecified, double deltaTime = Scene::DeltaTime())", asFUNCTION(MathSmoothDampNVec4), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Vec4 SmoothDamp(const Vec4& in from, const Vec4& in to, Vec4& inout velocity, double smoothTime, double maxSpeed, double deltaTime = Scene::DeltaTime())", asFUNCTION(MathSmoothDampVec4), asCALL_CDECL); assert(r >= 0);

		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
