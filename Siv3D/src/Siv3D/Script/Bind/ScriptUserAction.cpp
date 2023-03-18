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
# include <Siv3D/UserAction.hpp>

namespace s3d
{
	using namespace AngelScript;

	namespace detail
	{
		static constexpr uint32 CloseButtonClicked	= UserAction::CloseButtonClicked;
		static constexpr uint32 EscapeKeyDown		= UserAction::EscapeKeyDown;
		static constexpr uint32 WindowDeactivated	= UserAction::WindowDeactivated;
		static constexpr uint32 AnyKeyDown			= UserAction::AnyKeyDown;
		static constexpr uint32 MouseButtonDown		= UserAction::MouseButtonDown;
		static constexpr uint32 AnyKeyOrMouseDown	= UserAction::AnyKeyOrMouseDown;
		static constexpr uint32 Default				= UserAction::Default;
		static constexpr uint32 NoAction			= UserAction::NoAction;
	}

	void RegisterUserAction(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("UserAction"); assert(r >= 0);
		{
			r = engine->RegisterGlobalProperty("const uint32 CloseButtonClicked", (void*)&detail::CloseButtonClicked); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const uint32 EscapeKeyDown", (void*)&detail::EscapeKeyDown); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const uint32 WindowDeactivated", (void*)&detail::WindowDeactivated); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const uint32 AnyKeyDown", (void*)&detail::AnyKeyDown); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const uint32 MouseButtonDown", (void*)&detail::MouseButtonDown); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const uint32 AnyKeyOrMouseDown", (void*)&detail::AnyKeyOrMouseDown); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const uint32 Default", (void*)&detail::Default); assert(r >= 0);
			r = engine->RegisterGlobalProperty("const uint32 NoAction", (void*)&detail::NoAction); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
