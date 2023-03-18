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
# include <Siv3D/Mouse.hpp>
# include "../angelscript/scriptarray.h"

namespace s3d
{
	using namespace AngelScript;

	static const CScriptArray* MouseGetAllInputs()
	{
		const auto& inputs = Mouse::GetAllInputs();

		asITypeInfo* typeID = asGetActiveContext()->GetEngine()->GetTypeInfoByDecl("Array<Input>");

		if (void* mem = std::malloc(inputs.size_bytes() + sizeof(asUINT)))
		{
			*(asUINT*)mem = static_cast<asUINT>(inputs.size());
			std::memcpy(((asUINT*)mem) + 1, inputs.data(), inputs.size_bytes());

			const auto p = CScriptArray::Create(typeID, mem);
			std::free(mem);

			return p;
		}
		else
		{
			return nullptr;
		}
	}

	void RegisterMouse(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->RegisterGlobalProperty("const Input MouseL", (void*)&MouseL); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input MouseR", (void*)&MouseR); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input MouseM", (void*)&MouseM); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input MouseX1", (void*)&MouseX1); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input MouseX2", (void*)&MouseX2); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input MouseX3", (void*)&MouseX3); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input MouseX4", (void*)&MouseX4); assert(r >= 0);
		r = engine->RegisterGlobalProperty("const Input MouseX5", (void*)&MouseX5); assert(r >= 0);

		r = engine->SetDefaultNamespace("Mouse"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("Array<Input>@ GetAllInputs()", asFUNCTION(MouseGetAllInputs), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("double Wheel()", asFUNCTION(Mouse::Wheel), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("double WheelH()", asFUNCTION(Mouse::WheelH), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
