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

# include <Siv3D/SimpleGUIManager.hpp>
# include "SimpleGUIManagerDetail.hpp"

namespace s3d
{
	SimpleGUIManager::SimpleGUIManager()
		: pImpl(std::make_shared<SimpleGUIManagerDetail>())
	{

	}

	SimpleGUIManager::SimpleGUIManager(const FilePathView path)
		: SimpleGUIManager()
	{
		load(path);
	}

	SimpleGUIManager::~SimpleGUIManager()
	{

	}

	bool SimpleGUIManager::load(const FilePathView path, const bool verbose)
	{
		return pImpl->load(path, verbose);
	}

	bool SimpleGUIManager::save(const FilePathView path) const
	{
		return pImpl->save(path);
	}

	void SimpleGUIManager::draw() const
	{
		pImpl->draw();
	}

	bool SimpleGUIManager::hasChanged(const StringView name) const
	{
		return pImpl->hasChanged(name);
	}

	RectF SimpleGUIManager::region(const StringView name) const
	{
		return pImpl->region(name);
	}

	bool SimpleGUIManager::button(const StringView name) const
	{
		return pImpl->button(name);
	}

	double SimpleGUIManager::slider(const StringView name) const
	{
		return pImpl->slider(name);
	}

	double SimpleGUIManager::verticalSlider(const StringView name) const
	{
		return pImpl->verticalSlider(name);
	}

	bool SimpleGUIManager::checkBox(const StringView name) const
	{
		return pImpl->checkBox(name);
	}

	size_t SimpleGUIManager::radioButtons(const StringView name) const
	{
		return pImpl->radioButtons(name);
	}

	const TextEditState& SimpleGUIManager::textBox(const StringView name) const
	{
		return pImpl->textBox(name);
	}

	HSV SimpleGUIManager::colorPicker(const StringView name) const
	{
		return pImpl->colorPicker(name);
	}
}
