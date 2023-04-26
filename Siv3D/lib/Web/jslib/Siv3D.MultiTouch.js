mergeInto(LibraryManager.library, { 
    $siv3dActiveTouches: [],

    $siv3dAdjustPoint: function (x, y) {
        const rect = Module["canvas"].getBoundingClientRect();
        const cw = Module["canvas"].width;
        const ch = Module["canvas"].height;

        const scrollX = ((typeof window.scrollX !== 'undefined') ? window.scrollX : window.pageXOffset);
        const scrollY = ((typeof window.scrollY !== 'undefined') ? window.scrollY : window.pageYOffset);

        let adjustedX = x - (scrollX + rect.left);
        let adjustedY = y - (scrollY + rect.top);

        adjustedX = adjustedX * (cw / rect.width);
        adjustedY = adjustedY * (ch / rect.height);

        return { x: adjustedX, y: adjustedY };
    },
    
    $siv3dOnTouchStart: function(e) {
        siv3dActiveTouches = Array.from(e.touches);
        // e.preventDefault()
    },

    $siv3dOnTouchEnd: function(e) {
        siv3dActiveTouches = Array.from(e.touches);
        // e.stopPropagation();
    },

    $siv3dOnTouchMove: function(e) {
        siv3dActiveTouches = Array.from(e.touches);
        // e.stopPropagation();
    },

    siv3dRegisterTouchCallback: function() {
        Module["canvas"].addEventListener("touchstart", siv3dOnTouchStart);
        Module["canvas"].addEventListener("touchmove", siv3dOnTouchMove);
    },
    siv3dRegisterTouchCallback__sig: "v",
    siv3dRegisterTouchCallback__proxy: "sync",
    siv3dRegisterTouchCallback__deps: [ "$siv3dOnTouchMove", "$siv3dOnTouchStart", "$siv3dActiveTouches" ],

    siv3dUnregisterTouchCallback: function() {
        Module["canvas"].removeEventListener("touchstart", siv3dOnTouchStart);
        Module["canvas"].removeEventListener("touchmove", siv3dOnTouchMove);
    },
    siv3dUnregisterTouchCallback__sig: "v",
    siv3dUnregisterTouchCallback__proxy: "sync",
    siv3dUnregisterTouchCallback__deps: [ "$siv3dOnTouchMove", "$siv3dOnTouchStart" ],

    siv3dGetPrimaryTouchPoint: function(pX, pY) {
        if (siv3dActiveTouches.length > 0) {
            const touch = siv3dActiveTouches[0];
            const adjusted = siv3dAdjustPoint(touch.pageX, touch.pageY);
            
            setValue(pX, adjusted.x, 'double');
            setValue(pY, adjusted.y, 'double');
            return 1;
        } else {
            return 0;
        }
    },
    siv3dGetPrimaryTouchPoint__sig: "iii",
    siv3dGetPrimaryTouchPoint__proxy: "sync",
    siv3dGetPrimaryTouchPoint__deps: [ "$siv3dActiveTouches", "$siv3dAdjustPoint" ],
});
