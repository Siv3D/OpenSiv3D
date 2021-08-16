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

# pragma once
# include <memory>
# include "Common.hpp"
# include "StringView.hpp"

namespace s3d
{
	class ManagedScript
	{
	public:

		SIV3D_NODISCARD_CXX20
		ManagedScript();

		SIV3D_NODISCARD_CXX20
		explicit ManagedScript(FilePathView path);

		~ManagedScript();

		[[nodiscard]]
		bool isEmpty() const;

		[[nodiscard]]
		explicit operator bool() const;

		[[nodiscard]]
		bool compiled() const;

		void run() const;

	private:

		class ManagedScriptDetail;

		std::shared_ptr<ManagedScriptDetail> pImpl;
	};
}
