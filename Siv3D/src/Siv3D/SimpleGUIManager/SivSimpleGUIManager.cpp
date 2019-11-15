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
}
