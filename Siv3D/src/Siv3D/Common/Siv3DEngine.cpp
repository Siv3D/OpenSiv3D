﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "Siv3DEngine.hpp"
# include <Siv3D/Dummy/IDummy.hpp>
# include <Siv3D/LicenseManager/ILicenseManager.hpp>
# include <Siv3D/Logger/ILogger.hpp>
# include <Siv3D/System/ISystem.hpp>
# include <Siv3D/Resource/IResource.hpp>
# include <Siv3D/Profiler/IProfiler.hpp>
# include <Siv3D/ImageDecoder/IImageDecoder.hpp>
# include <Siv3D/ImageEncoder/IImageEncoder.hpp>
# include <Siv3D/UserAction/IUserAction.hpp>
# include <Siv3D/Scene/IScene.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Console/IConsole.hpp>
# include <Siv3D/Cursor/ICursor.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Addon/IAddon.hpp>

namespace s3d
{
	namespace detail
	{
		template <size_t I, class Tuple>
		static void Release(Tuple&& t)
		{
			std::get<I>(t).release();

			if constexpr (I > 0)
			{
				Release<I - 1>(t);
			}
		}

		template <class Tuple>
		static void ReleaseAll(Tuple&& t)
		{
			return Release<std::tuple_size_v<std::remove_reference_t<Tuple>> -1>(std::forward<Tuple>(t));
		}
	}

	Siv3DEngine::Siv3DEngine()
	{
		pEngine = this;
	}

	Siv3DEngine::~Siv3DEngine()
	{
		detail::ReleaseAll(m_components);
		
		pEngine = nullptr;
	}

	bool Siv3DEngine::isActive() noexcept
	{
		return (pEngine != nullptr);
	}
}
