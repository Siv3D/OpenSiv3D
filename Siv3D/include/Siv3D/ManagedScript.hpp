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
# include <memory>
# include "Fwd.hpp"

namespace s3d
{
	class ManagedScript
	{
	private:

		class ManagedScriptDetail;

		std::shared_ptr<ManagedScriptDetail> pImpl;

	public:

		ManagedScript();

		explicit ManagedScript(const FilePath& path);

		~ManagedScript();

		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] explicit operator bool() const;

		[[nodiscard]] bool compiled() const;

		void run() const;
	};
}
