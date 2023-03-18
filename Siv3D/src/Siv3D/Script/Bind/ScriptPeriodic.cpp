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
# include <Siv3D/Periodic.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterPeriodic(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Periodic"); assert(r >= 0);
		{		
			r = engine->RegisterGlobalFunction("double Sine0_1(const Duration& in, double = Scene::Time())", asFUNCTIONPR(Periodic::Sine0_1, (const Duration&, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Sine0_1(double, double = Scene::Time())", asFUNCTIONPR(Periodic::Sine0_1, (double, double), double), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("double Square0_1(const Duration& in, double = Scene::Time())", asFUNCTIONPR(Periodic::Square0_1, (const Duration&, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Square0_1(double, double = Scene::Time())", asFUNCTIONPR(Periodic::Square0_1, (double, double), double), asCALL_CDECL); assert(r >= 0);
		
			r = engine->RegisterGlobalFunction("double Triangle0_1(const Duration& in, double = Scene::Time())", asFUNCTIONPR(Periodic::Triangle0_1, (const Duration&, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Triangle0_1(double, double = Scene::Time())", asFUNCTIONPR(Periodic::Triangle0_1, (double, double), double), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("double Sawtooth0_1(const Duration& in, double = Scene::Time())", asFUNCTIONPR(Periodic::Sawtooth0_1, (const Duration&, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Sawtooth0_1(double, double = Scene::Time())", asFUNCTIONPR(Periodic::Sawtooth0_1, (double, double), double), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("double Jump0_1(const Duration& in, double = Scene::Time())", asFUNCTIONPR(Periodic::Jump0_1, (const Duration&, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Jump0_1(double, double = Scene::Time())", asFUNCTIONPR(Periodic::Jump0_1, (double, double), double), asCALL_CDECL); assert(r >= 0);


			r = engine->RegisterGlobalFunction("double Sine1_1(const Duration& in, double = Scene::Time())", asFUNCTIONPR(Periodic::Sine1_1, (const Duration&, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Sine1_1(double, double = Scene::Time())", asFUNCTIONPR(Periodic::Sine1_1, (double, double), double), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("double Square1_1(const Duration& in, double = Scene::Time())", asFUNCTIONPR(Periodic::Square1_1, (const Duration&, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Square1_1(double, double = Scene::Time())", asFUNCTIONPR(Periodic::Square1_1, (double, double), double), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("double Triangle1_1(const Duration& in, double = Scene::Time())", asFUNCTIONPR(Periodic::Triangle1_1, (const Duration&, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Triangle1_1(double, double = Scene::Time())", asFUNCTIONPR(Periodic::Triangle1_1, (double, double), double), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("double Sawtooth1_1(const Duration& in, double = Scene::Time())", asFUNCTIONPR(Periodic::Sawtooth1_1, (const Duration&, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Sawtooth1_1(double, double = Scene::Time())", asFUNCTIONPR(Periodic::Sawtooth1_1, (double, double), double), asCALL_CDECL); assert(r >= 0);

			r = engine->RegisterGlobalFunction("double Jump1_1(const Duration& in, double = Scene::Time())", asFUNCTIONPR(Periodic::Jump1_1, (const Duration&, double), double), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("double Jump1_1(double, double = Scene::Time())", asFUNCTIONPR(Periodic::Jump1_1, (double, double), double), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
