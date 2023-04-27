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

# if SIV3D_PLATFORM(WEB)
#   include <emscripten/threading.h>
#   include <emscripten/proxying.h>
# endif

namespace s3d
{
# if SIV3D_PLATFORM(WEB)

	namespace Platform::Web::System
	{
        namespace detail
        {
        # if defined(PROXY_TO_PTHREAD)
            __attribute__((import_name("siv3dSleepUntilWaked")))
            extern void siv3dSleepUntilWakedImpl(em_proxying_ctx*, void*);

            static int siv3dSleepUntilWaked()
            {
                auto defaultQueue = ::emscripten_proxy_get_system_queue();

                if (::emscripten_proxy_sync_with_ctx(
                    defaultQueue,
                    emscripten_main_browser_thread_id(),
                    &siv3dSleepUntilWakedImpl,
                    nullptr) == 1)
                {
                    return 0;
                }
                else
                {
                    return -1;
                }
            }
        # else
            __attribute__((import_name("siv3dSleepUntilWaked")))
            extern int siv3dSleepUntilWaked();
        # endif
        }

        /// @brief 指定した AsyncTask の準備ができるまで待機します
		template<class Type>
		Optional<Type> AwaitAsyncTask(AsyncTask<Type>& task)
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
