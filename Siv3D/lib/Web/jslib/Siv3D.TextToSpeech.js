mergeInto(LibraryManager.library, {
    siv3dRegisterTextToSpeechLanguagesUpdateHander: function(callback, callbackArg) {
        window.speechSynthesis.onvoiceschanged = function() {
            {{{ makeDynCall('vi', 'callback') }}}(callbackArg);
        };
    },
    siv3dRegisterTextToSpeechLanguagesUpdateHander__sig: "vii",
    siv3dRegisterTextToSpeechLanguagesUpdateHander__proxy: "sync",

    siv3dEnumerateAvailableTextToSpeechLanguages: function(returnPtr) {
        const LanguageNameToLanguageCodeList = {
            "ar-SA": 1025,
            "zh-CN": 2052,
            "zh-HK": 3076,
            "zh-TW": 1028,
            "en-AU": 3081,
            "en-GB": 2057,
            "en-US": 1033,
            "fr-FR": 1036,
            "de-DE": 1031,
            "hi-IN": 1081,
            "it-IT": 1040,
            "ja-JP": 1041,
            "ko-KR": 1042,
            "pt-BR": 1046,
            "ru-RU": 1049,
            "es-ES": 1034
        };
        
        const voices = window.speechSynthesis.getVoices();
        let listBufferPtr = Module["_malloc"](voices.length * 4 * 2);

        setValue(returnPtr, voices.length, "i32");
        setValue(returnPtr + 4, listBufferPtr, "i32");

        for(var i = 0; i < voices.length; i++) {
            const languageCode = LanguageNameToLanguageCodeList[voices[i].lang];
             
            setValue(listBufferPtr + 0, languageCode, "i32");
            setValue(listBufferPtr + 4, voices[i].default, "i32");

            listBufferPtr += 8;
        }
    },
    siv3dEnumerateAvailableTextToSpeechLanguages__sig: "vi",
    siv3dEnumerateAvailableTextToSpeechLanguages__proxy: "sync",

    siv3dStartTextToSpeechLanguages: function(textPtr, rate, volume, languageCode) {
        const LanguageCodeToLanguageNameList = {
            1025: "ar-SA",
            2052: "zh-CN",
            3076: "zh-HK",
            1028: "zh-TW",
            3081: "en-AU",
            2057: "en-GB",
            1033: "en-US",
            1036: "fr-FR",
            1031: "de-DE",
            1081: "hi-IN",
            1040: "it-IT",
            1041: "ja-JP",
            1042: "ko-KR",
            1046: "pt-BR",
            1049: "ru-RU",
            1034: "es-ES"
        };
        const text = UTF8ToString(textPtr);

        const speechUtter = new SpeechSynthesisUtterance(text);

        speechUtter.lang = LanguageCodeToLanguageNameList[languageCode];
        speechUtter.rate = rate;
        speechUtter.volume = volume;

        window.speechSynthesis.speak(speechUtter);
    },
    siv3dStartTextToSpeechLanguages__sig: "viiii",
    siv3dStartTextToSpeechLanguages__proxy: "sync",

    siv3dIsSpeakingTextToSpeechLanguages: function() {
        return window.speechSynthesis.speaking;
    },
    siv3dIsSpeakingTextToSpeechLanguages__sig: "iv",
    siv3dIsSpeakingTextToSpeechLanguages__proxy: "sync",

    siv3dPauseTextToSpeechLanguages: function() {
        window.speechSynthesis.pause();
    },
    siv3dPauseTextToSpeechLanguages__sig: "v",
    siv3dPauseTextToSpeechLanguages__proxy: "sync",

    siv3dResumeTextToSpeechLanguages: function() {
        window.speechSynthesis.resume();
    },
    siv3dResumeTextToSpeechLanguages__sig: "v",
    siv3dResumeTextToSpeechLanguages__proxy: "sync",
});
