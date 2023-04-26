mergeInto(LibraryManager.library, {
    $siv3dNotifications: [],

    siv3dRequestNotificationPermission: function(callback, callbackArg) {
        if (Notification.permission === "granted") {
            {{{ makeDynCall('vii', 'callback') }}}(1 /* NotificationPermission.Granted */, callbackArg);
            _siv3dMaybeAwake();
        } else {
            siv3dRegisterUserAction(function () {
                Notification.requestPermission().then(function(v) {
                    if (v === "granted") {
                        {{{ makeDynCall('vii', 'callback') }}}(1 /* NotificationPermission.Granted */, callbackArg);
                    } else {
                        {{{ makeDynCall('vii', 'callback') }}}(2 /* NotificationPermission.Denied */, callbackArg);
                    }
                    _siv3dMaybeAwake();
                });
            });
        }
    },
    siv3dRequestNotificationPermission__sig: "vii",
    siv3dRequestNotificationPermission__proxy: "sync",
    siv3dRequestNotificationPermission__deps: [ "siv3dMaybeAwake"],

    siv3dCreateNotification: function(title, body, actionsNum, actionTexts, callback, callbackArg) {
        if (!window.Notification && Notification.permission !== "granted") {
            {{{ makeDynCall('vii', 'callback') }}}(0, callbackArg);
            _siv3dMaybeAwake();
            return 0;
        }

        const idx = GL.getNewId(siv3dNotifications);

        const titleText = UTF8ToString(title);
        const bodyText = UTF8ToString(body);
        let actions = [];

        for (var i = 0; i < actionsNum; i++) {
            const textPtr = getValue(actionTexts + i * 4, "i32");
            const actionText = UTF8ToString(textPtr);

            actions.push({ title: actionText, action: actionText });
        }

        siv3dNotifications[idx] = new Notification(titleText, { body: bodyText, actions: actions });
        {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
        _siv3dMaybeAwake();

        return idx;
    },
    siv3dCreateNotification__sig: "iiiiiii",
    siv3dCreateNotification__proxy: "sync",
    siv3dCreateNotification__deps: [ "$siv3dRegisterUserAction", "$siv3dNotifications", "siv3dMaybeAwake" ],

    siv3dRegisterNotificationCallback: function(id, callback, callbackArg) {
        const notificattion = siv3dNotifications[id];

        notificattion.onclick = function() {
            {{{ makeDynCall('viii', 'callback') }}}(id, 1 /* ToastNotificationState.Activated */, callbackArg);
            _siv3dMaybeAwake();
        }
        notificattion.onshow = function() {
            {{{ makeDynCall('viii', 'callback') }}}(id, 2 /* ToastNotificationState.Shown */, callbackArg);
            _siv3dMaybeAwake();
        }
        notificattion.onclose = function() {
            {{{ makeDynCall('viii', 'callback') }}}(id, 5 /* ToastNotificationState.TimedOut */, callbackArg);
            _siv3dMaybeAwake();
        }
        notificattion.onerror = function() {
            {{{ makeDynCall('viii', 'callback') }}}(id, 6 /* ToastNotificationState.Error */, callbackArg);
            _siv3dMaybeAwake();
        }
    },
    siv3dRegisterNotificationCallback__sig: "viii",
    siv3dRegisterNotificationCallback__proxy: "sync",
    siv3dRegisterNotificationCallback__deps: [ "$siv3dNotifications", "siv3dMaybeAwake" ],

    siv3dCloseNotification: function(id) {
        const notificattion = siv3dNotifications[id];
        notificattion.close();

        delete siv3dNotifications[id];
    },
    siv3dCloseNotification__sig: "vi",
    siv3dCloseNotification__proxy: "sync",
    siv3dCloseNotification__deps: [ "$siv3dNotifications" ],

    siv3dQueryNotificationPermission: function() {
        const status = {
            "default": 0,
            "granted": 1,
            "denied": 2
        };
        return status[Notification.permission];
    },
    siv3dQueryNotificationPermission__sig: "iv",
    siv3dQueryNotificationPermission__proxy: "sync",
});