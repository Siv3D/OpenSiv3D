//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/ManagedScript.hpp>
# include "ManagedScriptDetail.hpp"

namespace s3d
{
	ManagedScript::ManagedScript()
		: pImpl(std::make_shared<ManagedScriptDetail>())
	{

	}

	ManagedScript::ManagedScript(const FilePath& path)
		: pImpl(std::make_shared<ManagedScriptDetail>(path))
	{

	}

	ManagedScript::~ManagedScript()
	{

	}

	bool ManagedScript::isEmpty() const
	{
		return pImpl->isEmpty();
	}

	ManagedScript::operator bool() const
	{
		return !isEmpty();
	}

	bool ManagedScript::compiled() const
	{
		return pImpl->compiled();
	}

	void ManagedScript::run() const
	{
		return pImpl->run();
	}
}
