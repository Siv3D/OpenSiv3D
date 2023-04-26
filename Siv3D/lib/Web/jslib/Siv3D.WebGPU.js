mergeInto(LibraryManager.library, {
    siv3dWebGPUConfigureSwapchain: function(deviceId, swapChainId, descriptor) {
        var device = WebGPU["mgrDevice"].get(deviceId);
        var swapChain = WebGPU["mgrSwapChain"].get(swapChainId);
        var width = {{{ makeGetValue('descriptor', C_STRUCTS.WGPUSwapChainDescriptor.width, 'u32', false) }}};
        var height = {{{ makeGetValue('descriptor', C_STRUCTS.WGPUSwapChainDescriptor.height, 'u32', false) }}};

        var desc = {
            "device": device,
            "format": WebGPU.TextureFormat[
                {{{ makeGetValue('descriptor', C_STRUCTS.WGPUSwapChainDescriptor.format, 'u32', false) }}}],
            "usage": {{{ makeGetValue('descriptor', C_STRUCTS.WGPUSwapChainDescriptor.usage, 'u32', false) }}},
            "size": { width, height }
        };

        swapChain["configure"](desc);
    },
    siv3dWebGPUConfigureSwapchain__sig: "viii",
    siv3dWebGPUConfigureSwapchain__proxy: "sync",
    siv3dWebGPUConfigureSwapchain__deps: [ "$WebGPU" ], 
});
