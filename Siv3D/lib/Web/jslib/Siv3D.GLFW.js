mergeInto(LibraryManager.library, { 
    glfwGetMonitorInfo_Siv3D: function(handle, displayID, xpos, ypos, w, h) {
        setValue(displayID, 1, 'i32');
        setValue(xpos, 0, 'i32');
        setValue(ypos, 0, 'i32');
        setValue(w, window.screen.width, 'i32');
        setValue(h, window.screen.height, 'i32');
    },
    glfwGetMonitorInfo_Siv3D__sig: "viiiiiiiiiii",
    glfwGetMonitorInfo_Siv3D__proxy: "sync",
    
    glfwGetMonitorWorkarea: function(handle, wx, wy, ww, wh) {
        setValue(wx, 0, 'i32');
        setValue(wy, 0, 'i32');
        setValue(ww, window.screen.availWidth, 'i32');
        setValue(wh, window.screen.availHeight, 'i32');
    },
    glfwGetMonitorWorkarea__sig: "viiiii",
    glfwGetMonitorWorkarea__proxy: "sync",

    glfwGetMonitorContentScale: function(handle, xscale, yscale) {
        setValue(xscale, 1, 'float');
        setValue(yscale, 1, 'float'); 
    },
    glfwGetMonitorContentScale__sig: "viii",
    glfwGetMonitorContentScale__proxy: "sync",

    glfwGetCursorPos__proxy: "sync",
    glfwCreateCursor__proxy: "sync",
    glfwSetCursorPos__proxy: "sync",
    glfwGetMonitors__proxy: "sync",
    glfwGetMonitorPhysicalSize__proxy: "sync",
    glfwGetVideoMode__proxy: "sync",
    glfwGetMonitorName__proxy: "sync",
    glfwMakeContextCurrent__proxy: "sync",
    glfwTerminate__proxy: "sync",
    glfwSetErrorCallback__proxy: "sync",
    glfwInit__proxy: "sync",
    glfwWindowHint__proxy: "sync",
    glfwCreateWindow__proxy: "sync",
    glfwSetWindowSizeLimits__proxy: "sync",
    glfwSetWindowUserPointer__proxy: "sync",
    glfwSetWindowPosCallback__proxy: "sync",
    glfwSetWindowSizeCallback__proxy: "sync",
    glfwSetFramebufferSizeCallback__proxy: "sync",
    glfwSetWindowIconifyCallback__proxy: "sync",
    glfwSetWindowFocusCallback__proxy: "sync",
    glfwPollEvents__proxy: "sync",
    glfwWindowShouldClose__proxy: "sync",
    glfwSetWindowShouldClose__proxy: "sync",
    glfwSetWindowTitle__proxy: "sync",
    glfwSetWindowPos__proxy: "sync",
    glfwMaximizeWindow__proxy: "sync",
    glfwRestoreWindow__proxy: "sync",
    glfwIconifyWindow__proxy: "sync",
    glfwSetWindowSize__proxy: "sync",
    glfwSetWindowSizeLimits__proxy: "sync",
    glfwGetFramebufferSize__proxy: "sync",
    glfwGetWindowPos__proxy: "sync",
    glfwGetWindowSize__proxy: "sync",
    glfwGetWindowAttrib__proxy: "sync",
    glfwGetWindowUserPointer__proxy: "sync",
});