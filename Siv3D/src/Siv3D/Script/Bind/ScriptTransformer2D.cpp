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
# include <Siv3D/Camera2D.hpp>
# include <Siv3D/Transformer2D.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	using namespace AngelScript;

	struct Transformer2DRef
	{
		std::shared_ptr<Transformer2D> m_data;

		Transformer2DRef() {}

		Transformer2DRef(const Mat3x2& mat, Transformer2D::Target target)
		{
			m_data = std::make_shared<Transformer2D>(mat, TransformCursor::Yes, target);
		}

		Transformer2DRef(const Mat3x2& mat, bool tc, Transformer2D::Target target)
		{
			m_data = std::make_shared<Transformer2D>(mat, TransformCursor{ tc }, target);
		}

		Transformer2DRef(const Mat3x2& mat, const Mat3x2& cmat, Transformer2D::Target target)
		{
			m_data = std::make_shared<Transformer2D>(mat, cmat, target);
		}

		static Transformer2DRef* Create()
		{
			return new Transformer2DRef();
		}

		static Transformer2DRef* Create(const Mat3x2& mat, int32 target)
		{
			return new Transformer2DRef(mat, ToEnum<Transformer2D::Target>(static_cast<uint8>(target)));
		}

		static Transformer2DRef* Create(const Mat3x2& mat, bool transformCursor, int32 target)
		{
			return new Transformer2DRef(mat, transformCursor, ToEnum<Transformer2D::Target>(static_cast<uint8>(target)));
		}

		static Transformer2DRef* Create(const Mat3x2& mat, const Mat3x2& cmat, int32 target)
		{
			return new Transformer2DRef(mat, cmat, ToEnum<Transformer2D::Target>(static_cast<uint8>(target)));
		}

		void Release()
		{
			delete this;
		}
	};

	using BindType = Transformer2D;

	static Transformer2DRef* Camera2DCreateTransformer(const Camera2D& camera)
	{
		return Transformer2DRef::Create(camera.getMat3x2(), FromEnum(Transformer2D::Target::PushCamera));
	}

	void RegisterTransformer2D(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		{
			constexpr char TypeName[] = "Transformer2D";

			r = engine->SetDefaultNamespace(TypeName); assert(r >= 0);
			{
				r = engine->RegisterEnum("Target"); assert(r >= 0);

				r = engine->RegisterEnumValue("Target", "PushLocal", static_cast<int32>(Transformer2D::Target::PushLocal)); assert(r >= 0);
				r = engine->RegisterEnumValue("Target", "PushCamera", static_cast<int32>(Transformer2D::Target::PushCamera)); assert(r >= 0);
				r = engine->RegisterEnumValue("Target", "SetLocal", static_cast<int32>(Transformer2D::Target::SetLocal)); assert(r >= 0);
				r = engine->RegisterEnumValue("Target", "SetCamera", static_cast<int32>(Transformer2D::Target::SetCamera)); assert(r >= 0);
			}
			r = engine->SetDefaultNamespace(""); assert(r >= 0);

			{
				r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Transformer2D@ f()", asFUNCTIONPR(Transformer2DRef::Create, (), Transformer2DRef*), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Transformer2D@ f(const Mat3x2& in, Transformer2D::Target)", asFUNCTIONPR(Transformer2DRef::Create, (const Mat3x2&, int32), Transformer2DRef*), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Transformer2D@ f(const Mat3x2& in, bool transformCursor = TransformCursor::No, Transformer2D::Target target = Transformer2D::Target::PushLocal) explicit", asFUNCTIONPR(Transformer2DRef::Create, (const Mat3x2&, bool, int32), Transformer2DRef*), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_FACTORY, "Transformer2D@ f(const Mat3x2& in, const Mat3x2& in, Transformer2D::Target target = Transformer2D::Target::PushLocal)", asFUNCTIONPR(Transformer2DRef::Create, (const Mat3x2&, const Mat3x2&, int32), Transformer2DRef*), asCALL_CDECL); assert(r >= 0);
				r = engine->RegisterObjectBehaviour(TypeName, asBEHAVE_RELEASE, "void f()", asMETHOD(Transformer2DRef, Release), asCALL_THISCALL); assert(r >= 0);

				r = engine->RegisterObjectMethod("Camera2D", "Transformer2D@ createTransformer() const", asFUNCTION(Camera2DCreateTransformer), asCALL_CDECL_OBJLAST); assert(r >= 0);
			}
		}
	}
}
