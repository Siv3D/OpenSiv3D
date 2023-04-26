mergeInto(LibraryManager.library, {
    $siv3dHasUserActionTriggered: false,
    $siv3dPendingUserActions: [],

    $siv3dTriggerUserAction: function() {
        for (var i = 0; i < siv3dPendingUserActions.length; i++) {
            (siv3dPendingUserActions[i])();
        }

        siv3dPendingUserActions.splice(0);
        siv3dHasUserActionTriggered = false;
    },
    $siv3dTriggerUserAction__deps: [ "$siv3dPendingUserActions" ],

    $siv3dRegisterUserAction: function(func) {
        siv3dPendingUserActions.push(func);
    },
    $siv3dRegisterUserAction__deps: [ "$siv3dPendingUserActions", "$autoResumeAudioContext", "$dynCall" ],

    $siv3dUserActionHookCallBack: function() {
        if (!siv3dHasUserActionTriggered) {
            setTimeout(siv3dTriggerUserAction, 30);
            siv3dHasUserActionTriggered = true;
        }
    },
    $siv3dUserActionHookCallBack__deps: [ "$siv3dHasUserActionTriggered", "$siv3dTriggerUserAction" ],

    $siv3dUserActionTouchEndCallBack: function(e) {
        siv3dTriggerUserAction();
        e.preventDefault();
    },
    $siv3dUserActionHookCallBack__deps: [ "$siv3dHasUserActionTriggered", "$siv3dTriggerUserAction" ],

    siv3dStartUserActionHook: function() {
        Module["canvas"].addEventListener('touchend', siv3dUserActionTouchEndCallBack);
        Module["canvas"].addEventListener('mousedown', siv3dUserActionHookCallBack);
        window.addEventListener('keydown', siv3dUserActionHookCallBack);
    },
    siv3dStartUserActionHook__sig: "v",
    siv3dStartUserActionHook__proxy: "sync",
    siv3dStartUserActionHook__deps: [ "$siv3dUserActionHookCallBack", "$siv3dUserActionTouchEndCallBack", "$siv3dHasUserActionTriggered" ],

    siv3dStopUserActionHook: function() {
        Module["canvas"].removeEventListener('touchend', siv3dUserActionTouchEndCallBack);
        Module["canvas"].removeEventListener('mousedown', siv3dUserActionHookCallBack);
        window.removeEventListener('keydown', siv3dUserActionHookCallBack);
    },
    siv3dStopUserActionHook__sig: "v",
    siv3dStopUserActionHook__proxy: "sync",
    siv3dStopUserActionHook__deps: [ "$siv3dUserActionHookCallBack", "$siv3dUserActionTouchEndCallBack" ],

});
