//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Audio.hpp>
# include <Siv3D/Audio/IAudio.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<Audio>>::AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`Audio` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Audio>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Audio))
		{
			p->release(m_id);
		}
	}

	Audio::Audio()
		: AssetHandle{ std::make_shared<AssetIDWrapperType>() }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	/*
	Font::Font(const int32 fontSize, const FilePathView path, const FontStyle style)
		: Font{ FontMethod::Bitmap, fontSize, path, 0, style } {}

	Font::Font(const int32 fontSize, const FilePathView path, const size_t faceIndex, const FontStyle style)
		: Font{ FontMethod::Bitmap, fontSize, path, faceIndex, style } {}

	Font::Font(const int32 fontSize, const Typeface typeface, const FontStyle style)
		: Font{ FontMethod::Bitmap, fontSize, typeface, style } {}

	Font::Font(const FontMethod fontMethod, const int32 fontSize, const FilePathView path, const FontStyle style)
		: Font{ fontMethod, fontSize, path, 0, style } {}

	Font::Font(const FontMethod fontMethod, const int32 fontSize, const FilePathView path, const size_t faceIndex, const FontStyle style)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Font)->create(path, faceIndex, fontMethod, fontSize, style)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Font::Font(const FontMethod fontMethod, const int32 fontSize, const Typeface typeface, const FontStyle style)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Font)->create(typeface, fontMethod, fontSize, style)) }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Font::~Font()
	{

	}

	bool Font::addFallback(const Font& font) const
	{
		if (not font)
		{
			LOG_FAIL(U"Font::addFallback() failed (font is empty)");
			return false;
		}

		return SIV3D_ENGINE(Font)->addFallbackFont(m_handle->id(), font.m_handle);
	}

	const String& Font::familyName() const
	{
		return SIV3D_ENGINE(Font)->getProperty(m_handle->id()).familiyName;
	}
	*/
}
