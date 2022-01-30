Module["getCurrentAudioContext"] = function() {
    return Module["SDL2"].audioContext;
};

Module["getCurrentAudioSource"] = function() {
    return Module["SDL2"].audio.scriptProcessorNode;
};
