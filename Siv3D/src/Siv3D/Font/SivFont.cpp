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

# include <Siv3D/Font.hpp>
# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/AssetMonitor/IAssetMonitor.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<Font>>::AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`Font` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Font>>::~AssetIDWrapper()
	{
		if (not Siv3DEngine::isActive())
		{
			return;
		}

		if (auto p = SIV3D_ENGINE(Font))
		{
			p->release(m_id);
		}
	}

	Font::Font()
		: AssetHandle{ std::make_shared<AssetIDWrapperType>() }
	{
		SIV3D_ENGINE(AssetMonitor)->created();
	}

	Font::Font(const int32 fontSize, const FilePathView path, const FontStyle style)
		: AssetHandle{ std::make_shared<AssetIDWrapperType>(SIV3D_ENGINE(Font)->create(path, fontSize, style)) } {}

	Font::~Font()
	{

	}

	const String& Font::getFamilyName() const
	{
		return SIV3D_ENGINE(Font)->getFamilyName(m_handle->id());
	}

	const String& Font::getStyleName() const
	{
		return SIV3D_ENGINE(Font)->getStyleName(m_handle->id());
	}

	FontStyle Font::getStyle() const
	{
		return SIV3D_ENGINE(Font)->getStyle(m_handle->id());
	}

	int32 Font::getFontSize() const
	{
		return SIV3D_ENGINE(Font)->getFontSize(m_handle->id());
	}

	int32 Font::getAscent() const
	{
		return SIV3D_ENGINE(Font)->getAscent(m_handle->id());
	}

	int32 Font::getDescent() const
	{
		return SIV3D_ENGINE(Font)->getDescent(m_handle->id());
	}
}
