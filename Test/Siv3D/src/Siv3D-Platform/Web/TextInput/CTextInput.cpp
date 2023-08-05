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

# include <Siv3DTest.hpp>
# include <Siv3D/TextInput/CTextInput.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <emscripten.h>

EM_JS(void, dispatchInput, (const char *text), {
    const e = new InputEvent('input', {
        inputType: 'insertText',
        data: UTF8ToString(text)
    });
    siv3dTextInputElement.dispatchEvent(e);
})

EM_JS(void, dispatchBackspace, (), {
    const e = new InputEvent('input', {
        inputType: 'deleteContentBackward'
    });
    siv3dTextInputElement.dispatchEvent(e);
})

EM_JS(void, dispatchDelete, (), {
    const e = new InputEvent('input', {
        inputType: 'deleteContentForward'
    });
    siv3dTextInputElement.dispatchEvent(e);
})

EM_JS(void, dispatchCompositionInput, (const char *text), {
    const e = new InputEvent('input', {
        inputType: 'insertCompositionText',
        data: UTF8ToString(text)
    });
    siv3dTextInputElement.dispatchEvent(e);
})

EM_JS(void, dispatchCompositionBeforeInput, (const char *text, const char *before, int startOffset, int endOffset), {
    const targetRanges = [];
    
    if (before !== 0) {
        const text = document.createTextNode(UTF8ToString(before));
        targetRanges.push(new StaticRange({
            startContainer: text,
            startOffset,
            endContainer: text,
            endOffset
        }));
    }
    
    const e = new InputEvent('beforeinput', {
        inputType: 'insertCompositionText',
        data: UTF8ToString(text),
        targetRanges
    });
    siv3dTextInputElement.dispatchEvent(e);
})

EM_JS(void, dispatchCompositionStart, (const char *text), {
    const e = new CompositionEvent('compositionstart', {
        data: UTF8ToString(text)
    });
    siv3dTextInputElement.dispatchEvent(e);
})

EM_JS(void, dispatchCompositionUpdate, (const char *text), {
    const e = new CompositionEvent('compositionupdate', {
        data: UTF8ToString(text)
    });
    siv3dTextInputElement.dispatchEvent(e);
})

EM_JS(void, dispatchCompositionEnd, (const char *text), {
    const e = new CompositionEvent('compositionend', {
        data: UTF8ToString(text)
    });
    siv3dTextInputElement.dispatchEvent(e);
})

TEST_CASE("TextInput::getChars")
{
    const auto cTextInput = Siv3DEngine::Get<ISiv3DTextInput>();

    SECTION("Simple input")
    {
        dispatchInput("Siv3D");

        cTextInput->update();
        const auto chars = cTextInput->getChars();

        REQUIRE(chars == U"Siv3D");
    }

    SECTION("BackSpace")
    {
        dispatchInput("Siv");
        dispatchBackspace();
        dispatchInput("3D");

        cTextInput->update();
        const auto chars = cTextInput->getChars();

        REQUIRE(chars == U"Siv\b3D");
    }

    SECTION("Delete")
    {
        dispatchInput("Siv");
        dispatchDelete();
        dispatchInput("3D");

        cTextInput->update();
        const auto chars = cTextInput->getChars();

        REQUIRE(chars == U"Siv\x7F""3D");
    }
}

TEST_CASE("TextInput::getEditingText")
{
    const auto cTextInput = Siv3DEngine::Get<ISiv3DTextInput>();

    // Composition イベントはブラウザ、OS によって発火順番が異なる。
    // それぞれのブラウザ、OS での発火順番をエミュレートし、どれでも問題なくテキスト入力ができることを確かめる。
    SECTION("Chrome on Windows")
    {
        // 入力1: s
        {
            dispatchCompositionStart("");
            dispatchCompositionUpdate("ｓ");
            dispatchCompositionBeforeInput("ｓ", nullptr, 0, 0);
            dispatchCompositionInput("ｓ");

            cTextInput->update();
            REQUIRE(cTextInput->getChars() == U"");
            REQUIRE(cTextInput->getEditingText() == U"ｓ");
        }

        // 入力2: i
        {
            dispatchCompositionUpdate("し");
            dispatchCompositionBeforeInput("し", "ｓ", 0, 1);
            dispatchCompositionInput("し");

            cTextInput->update();
            REQUIRE(cTextInput->getChars() == U"");
            REQUIRE(cTextInput->getEditingText() == U"し");
        }
        
        // 入力3: Enter (確定)
        {
            dispatchCompositionBeforeInput("し", "ｓ", 0, 1);
            dispatchCompositionInput("し");
            dispatchCompositionEnd("し");

            cTextInput->update();
            REQUIRE(cTextInput->getChars() == U"し");
            REQUIRE(cTextInput->getEditingText() == U"");
        }
        
    }

    SECTION("FireFox on Windows")
    {
        // 入力1: s
        {
            dispatchCompositionStart("");
            dispatchCompositionUpdate("ｓ");
            dispatchCompositionBeforeInput("ｓ", nullptr, 0, 0);
            dispatchCompositionInput("ｓ");

            cTextInput->update();
            REQUIRE(cTextInput->getChars() == U"");
            REQUIRE(cTextInput->getEditingText() == U"ｓ");
        }

        // 入力2: i
        {
            dispatchCompositionUpdate("し");
            dispatchCompositionBeforeInput("し", "ｓ", 0, 1);
            dispatchCompositionInput("し");

            cTextInput->update();
            REQUIRE(cTextInput->getChars() == U"");
            REQUIRE(cTextInput->getEditingText() == U"し");
        }
        
        // 入力3: Enter (確定)
        {
            dispatchCompositionBeforeInput("し", "ｓ", 0, 1);
            dispatchCompositionEnd("し"); // input イベントより先になる
            dispatchCompositionInput("し");

            cTextInput->update();
            REQUIRE(cTextInput->getChars() == U"し");
            REQUIRE(cTextInput->getEditingText() == U"");
        }   
    }

    SECTION("FireFox on Android")
    {
        // 入力1: s
        {
            dispatchCompositionStart("");
            dispatchCompositionUpdate("し");
            dispatchCompositionBeforeInput("し", nullptr, 0, 0);
            dispatchCompositionInput("し");

            cTextInput->update();
            REQUIRE(cTextInput->getChars() == U"");
            REQUIRE(cTextInput->getEditingText() == U"し");
        }
        
        // 入力2: 入力候補から確定
        {
            dispatchCompositionUpdate("渋");
            dispatchCompositionBeforeInput("渋", "し", 0, 1);
            dispatchCompositionEnd("渋"); // input イベントより先になる
            dispatchCompositionInput("渋");

            cTextInput->update();
            REQUIRE(cTextInput->getChars() == U"渋");
            REQUIRE(cTextInput->getEditingText() == U"");
        }   
    }

    SECTION("FireFox on Android in English")
    {
        // 入力1: すでに Siv と入力があるところにカーソルを合わせる
        {
            dispatchCompositionStart("");
            dispatchCompositionUpdate("Siv");
            
            cTextInput->update();
            REQUIRE(cTextInput->getChars() == U"");
            REQUIRE(cTextInput->getEditingText() == U"Siv");
        }
        
        // 入力2: Siv3D を入力候補から選択
        {
            dispatchCompositionBeforeInput("Siv3D", "Siv ", 0, 3);
            dispatchCompositionUpdate("Siv3D");
            dispatchCompositionInput("Siv3D");
            dispatchCompositionEnd("Siv3D");

            cTextInput->update();
            REQUIRE(cTextInput->getChars() == U"\x08\x08\x08Siv3D");
            REQUIRE(cTextInput->getEditingText() == U"");
        }   
    }
}
