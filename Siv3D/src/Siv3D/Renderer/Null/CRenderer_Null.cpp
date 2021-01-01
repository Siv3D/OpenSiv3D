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

# include "CRenderer_Null.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Scene.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CRenderer_Null::CRenderer_Null() = default;

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

		clear();
	}

	StringView CRenderer_Null::getName() const
	{
		static constexpr StringView name(U"Null");
		return name;
	}

	void CRenderer_Null::clear()
	{

	}

	void CRenderer_Null::flush()
	{

	}

	bool CRenderer_Null::present()
	{
		return true;
	}

	void CRenderer_Null::setSceneResizeMode(ResizeMode)
	{

	}

	ResizeMode CRenderer_Null::getSceneResizeMode() const noexcept
	{
		return(Scene::DefaultResizeMode);
	}

	void CRenderer_Null::setSceneBufferSize(Size)
	{
		
	}

	Size CRenderer_Null::getSceneBufferSize() const noexcept
	{
		return Size(0, 0);
	}

	void CRenderer_Null::setSceneTextureFilter(const TextureFilter)
	{

	}

	TextureFilter CRenderer_Null::getSceneTextureFilter() const noexcept
	{
		return Scene::DefaultTextureFilter;
	}

	void CRenderer_Null::setBackgroundColor(const ColorF&)
	{

	}

	const ColorF& CRenderer_Null::getBackgroundColor() const noexcept
	{
		static constexpr ColorF backgroundColor = Scene::DefaultBackgroundColor;
		return backgroundColor;
	}

	void CRenderer_Null::setLetterboxColor(const ColorF&)
	{

	}

	const ColorF& CRenderer_Null::getLetterboxColor() const noexcept
	{
		static constexpr ColorF letterBoxColor = Scene::DefaultLetterBoxColor;
		return letterBoxColor;
	}

	std::pair<float, RectF> CRenderer_Null::getLetterboxComposition() const noexcept
	{
		return{ 1, { 0, 0, 0, 0 } };
	}
}
