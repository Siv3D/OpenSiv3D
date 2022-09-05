Module["getCurrentAudioContext"] = function() {
    return Module["SDL2"].audioContext;
};
  
Module["getCurrentAudioSource"] = function() {
    return Module["SDL2"].audio.scriptProcessorNode;
};
  
// TODO: fix emscripten side
Module["setFramebufferSize"] = function(width, height) {
    if (!GLFW.active) return;
    let resizeNeeded = true;
  
    if (GLFW.active.width != width || GLFW.active.height != height) {
      GLFW.active.width = width;
      GLFW.active.height = height;
    } else {
      resizeNeeded = false;
    }
  
    if (resizeNeeded) {
      const canvas = Module['canvas'];
      canvas.width = GLFW.active.width;
      canvas.height = GLFW.active.height;
  
      GLFW.onWindowSizeChanged();
      GLFW.onFramebufferSizeChanged();
    }
};
  