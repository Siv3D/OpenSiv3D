//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
# if SIV3D_PLATFORM(WEB)

	namespace Platform::Web::System
	{
        namespace detail
        {
            __attribute__((import_name("siv3dSleepUntilWaked")))
            int siv3dSleepUntilWaked();
        }

        /// @brief 指定した AsyncTask の準備ができるまで待機します
		template<class Type>
		Optional<Type> WaitForFutureResolved(AsyncTask<Type>& task)
        {
            while (!task.isReady())
            {
                if (detail::siv3dSleepUntilWaked() != 0)
                {
                    return none;
                }
            }

            return std::move(task.get());
        }
    }

# endif
}
