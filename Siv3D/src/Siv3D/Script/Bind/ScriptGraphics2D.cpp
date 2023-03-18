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
# include <Siv3D/Graphics2D.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterGraphics2D(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("Graphics2D"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("Float4 GetColorMul()", asFUNCTION(Graphics2D::GetColorMul), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Float4 GetColorAdd()", asFUNCTION(Graphics2D::GetColorAdd), asCALL_CDECL); assert(r >= 0);

			// ...
			
			r = engine->RegisterGlobalFunction("void SetScissorRect()", asFUNCTION(Graphics2D::SetScissorRect), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Rect GetScissorRect()", asFUNCTION(Graphics2D::GetScissorRect), asCALL_CDECL); assert(r >= 0);

			// ...

			r = engine->RegisterGlobalFunction("const Mat3x2& GetLocalTransform()", asFUNCTION(Graphics2D::GetLocalTransform), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("const Mat3x2& GetCameraTransform()", asFUNCTION(Graphics2D::GetCameraTransform), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("float GetMaxScaling()", asFUNCTION(Graphics2D::GetMaxScaling), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("Point GetRenderTargetSize()", asFUNCTION(Graphics2D::GetRenderTargetSize), asCALL_CDECL); assert(r >= 0);

			// ...

			r = engine->RegisterGlobalFunction("void Flush()", asFUNCTION(Graphics2D::Flush), asCALL_CDECL); assert(r >= 0);

			// ...
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
