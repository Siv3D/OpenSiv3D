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

# include <Siv3D/Keyboard.hpp>
# include <Siv3D/Keyboard/IKeyboard.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Keyboard
	{
		const Array<Input>& GetAllInputs() noexcept
		{
			return SIV3D_ENGINE(Keyboard)->getAllInput();
		}
	}

# if SIV3D_PLATFORM(WINDOWS)

	namespace Platform::Windows::Keyboard
	{
		Array<KeyEvent> GetEvents()
		{
			return SIV3D_ENGINE(Keyboard)->getEvents();
		}
	}

# endif
}
