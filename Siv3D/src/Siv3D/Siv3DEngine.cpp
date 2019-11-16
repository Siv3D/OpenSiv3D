//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "Siv3DEngine.hpp"
# include "LicenseManager/ILicenseManager.hpp"
# include "Logger/ILogger.hpp"
# include "System/ISystem.hpp"
# include "CPU/ICPU.hpp"
# include "Profiler/IProfiler.hpp"
# include "ImageFormat/IImageFormat.hpp"
# include "ObjectDetection/IObjectDetection.hpp"
# include "Window/IWindow.hpp"
# include "Console/IConsole.hpp"
# include "Cursor/ICursor.hpp"
# include "Keyboard/IKeyboard.hpp"
# include "Mouse/IMouse.hpp"
# include "Gamepad/IGamepad.hpp"
# include "XInput/IXInput.hpp"
# include "TextInput/ITextInput.hpp"
# include "TextToSpeech/ITextToSpeech.hpp"
# include "Clipboard/IClipboard.hpp"
# include "DragDrop/IDragDrop.hpp"
# include "Codec/ICodec.hpp"
# include "AudioFormat/IAudioFormat.hpp"
# include "SoundFont/ISoundFont.hpp"
# include "Audio/IAudio.hpp"
# include "FFT/IFFT.hpp"
# include "Network/INetwork.hpp"
# include "ToastNotification/IToastNotification.hpp"
# include "Graphics/IGraphics.hpp"
# include "Shader/IShader.hpp"
# include "Texture/ITexture.hpp"
# include "Renderer2D/IRenderer2D.hpp"
# include "ScreenCapture/IScreenCapture.hpp"
# include "Font/IFont.hpp"
# include "SDFFont/ISDFFont.hpp"
# include "GUI/IGUI.hpp"
# include "Effect/IEffect.hpp"
# include "Print/IPrint.hpp"
# include "Script/IScript.hpp"
# include "Asset/IAsset.hpp"

namespace s3d
{
	Siv3DEngine::Siv3DEngine()
	{
		pEngine = this;
	}

	Siv3DEngine::~Siv3DEngine()
	{
		ReleaseAllComponents(m_interfaces);
		pEngine = nullptr;
	}
}
