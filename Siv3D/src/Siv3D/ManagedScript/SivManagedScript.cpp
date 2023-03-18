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

# include <Siv3D/ManagedScript.hpp>
# include <Siv3D/ManagedScript/ManagedScriptDetail.hpp>

namespace s3d
{
	ManagedScript::ManagedScript()
		: pImpl{ std::make_shared<ManagedScriptDetail>() } {}

	ManagedScript::ManagedScript(const FilePathView path)
		: pImpl{ std::make_shared<ManagedScriptDetail>(path) } {}

	ManagedScript::~ManagedScript() {}

	bool ManagedScript::isEmpty() const
	{
		return pImpl->isEmpty();
	}

	ManagedScript::operator bool() const
	{
		return (not pImpl->isEmpty());
	}

	bool ManagedScript::compiled() const
	{
		return pImpl->compiled();
	}

	void ManagedScript::setTriggerToReload(const std::function<bool(void)>& trigger)
	{
		pImpl->setTriggerToReload(trigger);
	}

	const Array<FilePath>& ManagedScript::getIncludedFiles() const noexcept
	{
		return pImpl->getIncludedFiles();
	}

	void ManagedScript::run() const
	{
		return pImpl->run();
	}
}
