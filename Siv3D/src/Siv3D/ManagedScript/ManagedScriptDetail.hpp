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

# pragma once
# include <Siv3D/Script.hpp>
# include <Siv3D/ManagedScript.hpp>

namespace s3d
{
	class ManagedScript::ManagedScriptDetail
	{
	private:

		Script m_script;

		std::function<bool()> m_callback;

		std::function<void()> m_main;

		bool m_requestReload = false;

	public:

		ManagedScriptDetail();

		explicit ManagedScriptDetail(const FilePath& path);

		~ManagedScriptDetail();

		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] bool compiled() const;

		void run();
	};
}
