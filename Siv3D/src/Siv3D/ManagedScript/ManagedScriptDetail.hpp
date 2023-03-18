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

# pragma once
# include <Siv3D/ManagedScript.hpp>
# include <Siv3D/Script.hpp>

namespace s3d
{
	class ManagedScript::ManagedScriptDetail
	{
	public:

		ManagedScriptDetail();

		explicit ManagedScriptDetail(FilePathView path);

		~ManagedScriptDetail();

		[[nodiscard]]
		bool isEmpty() const;

		[[nodiscard]]
		bool compiled() const;

		void setTriggerToReload(const std::function<bool()>& trigger);

		const Array<FilePath>& getIncludedFiles() const noexcept;

		void run();

		[[nodiscard]]
		bool hasException() const;

		void clearException();

	private:

		Script m_script;

		std::function<bool()> m_triggerToReload;

		std::function<bool()> m_callback;

		ScriptFunction<void()> m_main;

		bool m_requestReload = false;

		bool m_hasException = false;
	};
}
