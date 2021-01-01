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

# include <Siv3D/Texture.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FreestandingMessageBox/FreestandingMessageBox.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<Texture>>::AssetIDWrapper()
	{
		if (!Siv3DEngine::isActive())
		{
			FreestandingMessageBox::ShowError(U"`Texture` must be initialized after engine-setup. Please fix the C++ code.");
			std::abort();
		}
	}

	template <>
	AssetIDWrapper<AssetHandle<Texture>>::~AssetIDWrapper()
	{
		LOG_INFO(U"pTexture->release({})"_fmt(m_id.value()));
	}

	Texture::Texture()
	{

	}

	Texture::Texture(const FilePathView path)
		: Texture(Image(path))
	{

	}

	Texture::Texture(const Image&)
		: AssetHandle(std::make_shared<AssetIDWrapperType>(AssetIDWrapperType::IDType{ 1 }))
	{

	}
}
