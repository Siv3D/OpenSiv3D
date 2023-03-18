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

# include "CRenderer_Null.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/Mesh/IMesh.hpp>
# include <Siv3D/Renderer2D/Null/CRenderer2D_Null.hpp>
# include <Siv3D/Texture/Null/CTexture_Null.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	CRenderer_Null::CRenderer_Null()
	{
		// do nothing
	}

	CRenderer_Null::~CRenderer_Null()
	{
		LOG_SCOPED_TRACE(U"CRenderer_Null::~CRenderer_Null()");
	}

	EngineOption::Renderer CRenderer_Null::getRendererType() const noexcept
	{
		return EngineOption::Renderer::Headless;
	}

	void CRenderer_Null::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_Null::init()");

		pTexture = static_cast<CTexture_Null*>(SIV3D_ENGINE(Texture));
		pRenderer2D = static_cast<CRenderer2D_Null*>(SIV3D_ENGINE(Renderer2D));

		SIV3D_ENGINE(Shader)->init();
		SIV3D_ENGINE(Mesh)->init();

		clear();
	}

	StringView CRenderer_Null::getName() const
	{
		static constexpr StringView name(U"Null");
		return name;
	}

	void CRenderer_Null::clear()
	{
		pRenderer2D->update();
	}

	void CRenderer_Null::flush()
	{
		// do nothing
	}

	bool CRenderer_Null::present()
	{
		return true;
	}

	void CRenderer_Null::setVSyncEnabled(bool)
	{
		// do nothing
	}

	bool CRenderer_Null::isVSyncEnabled() const
	{
		return false;
	}

	void CRenderer_Null::captureScreenshot()
	{
		// do nothing
	}

	const Image& CRenderer_Null::getScreenCapture() const
	{
		static const Image emptyImage{};
		return emptyImage;
	}

	void CRenderer_Null::setSceneResizeMode(ResizeMode)
	{
		// do nothing
	}

	ResizeMode CRenderer_Null::getSceneResizeMode() const noexcept
	{
		return(Scene::DefaultResizeMode);
	}

	void CRenderer_Null::setSceneBufferSize(Size)
	{
		// do nothing
	}

	Size CRenderer_Null::getSceneBufferSize() const noexcept
	{
		return Size{ 0, 0 };
	}

	void CRenderer_Null::setSceneTextureFilter(const TextureFilter)
	{
		// do nothing
	}

	TextureFilter CRenderer_Null::getSceneTextureFilter() const noexcept
	{
		return Scene::DefaultTextureFilter;
	}

	void CRenderer_Null::setBackgroundColor(const ColorF&)
	{
		// do nothing
	}

	const ColorF& CRenderer_Null::getBackgroundColor() const noexcept
	{
		static constexpr ColorF backgroundColor = Scene::DefaultBackgroundColor;
		return backgroundColor;
	}

	void CRenderer_Null::setLetterboxColor(const ColorF&)
	{
		// do nothing
	}

	const ColorF& CRenderer_Null::getLetterboxColor() const noexcept
	{
		static constexpr ColorF letterBoxColor = Scene::DefaultLetterBoxColor;
		return letterBoxColor;
	}

	std::pair<float, RectF> CRenderer_Null::getLetterboxComposition() const noexcept
	{
		return{ 1.0f, { 0, 0, 0, 0 } };
	}

	void CRenderer_Null::updateSceneSize()
	{
		// do nothing
	}
}
