export const projectCapability = {
    'browserstack.user': process.env.BROWSERSTACK_USERNAME,
    'browserstack.key': process.env.BROWSERSTACK_ACCESS_KEY,
    'seleniumVersion': 4,

    'browserstack.console': 'info',
    "browserstack.local": 'true',
    'friendlyBrowserName': '',
    'name': ''
}

export type Capability = typeof projectCapability & DeciceCapability;

export interface MobileCapability {
    os: "android" | "iOS",
    real_mobile: string,
    device: string,
    os_version: string,
    browserName: string
}

export interface DesktopCapability { 
    os: "Windows" | "OS X",
    os_version: string,
    browserName: string,
    browser_version: string
}

export type DeciceCapability = MobileCapability | DesktopCapability;

export const deviceCapabilities: DeciceCapability[] = [
    {
        'os' : 'Windows',
        'os_version' : '10',
        'browserName' : 'Chrome',
        'browser_version' : '98'
    },
    {
        'os' : 'Windows',
        'os_version' : '10',
        'browserName' : 'Edge',
        'browser_version' : '98'
    },
    {
        'os' : 'OS X',
        'os_version' : 'Monterey',
        'browserName' : 'Safari',
        'browser_version' : '15'
    },
    {
        'os' : 'android',
        "real_mobile" : "true",
        'device' : 'Google Pixel',
        'os_version' : '8.0',
        'browserName' : 'Chrome'
    },
    {
        'os' : 'android',
        "real_mobile" : "true",
        'device' : 'Google Pixel 6',
        'os_version' : '12.0',
        'browserName' : 'Chrome'
    },
    {
        'os' : 'android',
        "real_mobile" : "true",
        'device' : 'Samsung Galaxy S9 Plus',
        'os_version' : '8.0',
        'browserName' : 'Chrome'
    },
    {
        'os' : 'android',
        "real_mobile" : "true",
        'device' : 'Samsung Galaxy S21',
        'os_version' : '11.0',
        'browserName' : 'Chrome'
    },
    {
        'os' : 'iOS',
        "real_mobile" : "true",
        'device' : 'iPhone 11',
        'os_version' : '15',
        'browserName' : 'Safari'
    },
    {
        'os' : 'iOS',
        "real_mobile" : "true",
        'device' : 'iPhone XS',
        'os_version' : '15',
        'browserName' : 'Safari'
    },
    {
        'os' : 'iOS',
        "real_mobile" : "true",
        'device' : 'iPad 9th',
        'os_version' : '15',
        'browserName' : 'Safari'
    },
];

export const notSupportedDeviceCapabilities: DeciceCapability[] = [
    {
        'os' : 'iOS',
        "real_mobile" : "true",
        'device' : 'iPhone 11',
        'os_version' : '14',
        'browserName' : 'Safari'
    },
    {
        'os' : 'Windows',
        'os_version' : '10',
        'browserName' : 'Firefox',
        'browser_version' : '97'
    },
    {
        'os' : 'OS X',
        'os_version' : 'Big Sur',
        'browserName' : 'Safari',
        'browser_version' : '14'
    },
];

export function generateCapability(cap: DeciceCapability): Capability {
    const copyed = Object.assign({}, cap);
    let capability = Object.assign(copyed, projectCapability);

    if (capability.os === "Windows" || capability.os === "OS X") {
        capability.friendlyBrowserName = `${capability.os} ${capability.os_version}, ${capability.browserName} ${capability.browser_version}`;
    } else if (capability.os === "android" || capability.os === "iOS") {
        capability.friendlyBrowserName = `${capability.device} ${capability.browserName}`;
    }

    return capability;
}
