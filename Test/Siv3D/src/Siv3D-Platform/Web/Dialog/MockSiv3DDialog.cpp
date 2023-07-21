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

# include <future>
# include "MockSiv3DDialog.hpp"

String ReturenValue_siv3dOpenDialogAsync;

void SetReturnValue_siv3dOpenDialogAsync(const String& mockReturnValue)
{
    ReturenValue_siv3dOpenDialogAsync = mockReturnValue;
}

namespace s3d::Platform::Web::Dialog
{
    namespace detail
    {
        template <class T>
		using siv3dOpenDialogCallback = void (*)(char**, uint32, std::promise<T>*);

        template <class T>
        void siv3dOpenDialogImpl(const char* filter, siv3dOpenDialogCallback<T> callback, std::promise<T>* promise, bool allowMultiple)
        {
            if (not ReturenValue_siv3dOpenDialogAsync)
            {
                callback(nullptr, 0, promise);
            }
            else
            {
                auto narrowed = ReturenValue_siv3dOpenDialogAsync.narrow();
                char* files[] { const_cast<char*>(narrowed.c_str()) }; 
                callback(files, 1, promise);
            }
        }

        template void siv3dOpenDialogImpl<Optional<FilePath>>(const char* filter, siv3dOpenDialogCallback<Optional<FilePath>> callback, std::promise<Optional<FilePath>>* promise, bool allowMultiple);
        template void siv3dOpenDialogImpl<Array<FilePath>>(const char* filter, siv3dOpenDialogCallback<Array<FilePath>> callback, std::promise<Array<FilePath>>* promise, bool allowMultiple);
        template void siv3dOpenDialogImpl<Image>(const char* filter, siv3dOpenDialogCallback<Image> callback, std::promise<Image>* promise, bool allowMultiple);
        template void siv3dOpenDialogImpl<Texture>(const char* filter, siv3dOpenDialogCallback<Texture> callback, std::promise<Texture>* promise, bool allowMultiple);
        template void siv3dOpenDialogImpl<Wave>(const char* filter, siv3dOpenDialogCallback<Wave> callback, std::promise<Wave>* promise, bool allowMultiple);
        template void siv3dOpenDialogImpl<Audio>(const char* filter, siv3dOpenDialogCallback<Audio> callback, std::promise<Audio>* promise, bool allowMultiple);
    }
}
