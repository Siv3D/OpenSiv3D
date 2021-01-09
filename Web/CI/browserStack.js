const webdriver = require('selenium-webdriver');
      
const projectCapability = {
  'build': process.env.BROWSERSTACK_BUILD_NAME,
  'project': process.env.BROWSERSTACK_PROJECT_NAME,
  'browserstack.user': process.env.BROWSERSTACK_USERNAME,
  'browserstack.key': process.env.BROWSERSTACK_ACCESS_KEY,

  'browserstack.console': 'info'
}

const deviceCapabilities = [
  {
    'os' : 'Windows',
    'os_version' : '10',
    'browserName' : 'Chrome',
    'browser_version' : '87'
  },
  {
    'os' : 'Windows',
    'os_version' : '10',
    'browserName' : 'Edge',
    'browser_version' : '87'
  },
  {
    'os' : 'Windows',
    'os_version' : '10',
    'browserName' : 'Firefox',
    'browser_version' : '84'
  },
  {
    'os' : 'Mac',
    'os_version' : 'macOS Big Sur',
    'browserName' : 'Safari',
    'browser_version' : '14'
  },
  {
    'os' : 'android',
    'device' : 'Google Pixel 3a',
    'os_version' : '9.0',
    'browserName' : 'Chrome'
  },
  {
    'os' : 'iOS',
    'device' : 'iPhone XS',
    'os_version' : '14',
    'browserName' : 'Safari'
  }
];

const browserstackURL = 'https://hub-cloud.browserstack.com/wd/hub';
const testedSiteURL = 'https://siv3d-assets.kamenokosoft.com/v6-wasm-app/Siv3DTest';

/**
 * 
 * @param { number } milliSeconds 
 */
function sleep(milliSeconds) {
  return new Promise(resolve => setTimeout(resolve, milliSeconds));
}

/**
 * Mark test as passed
 * @param { webdriver.ThenableWebDriver } driver
 */
function reportAsPassed(driver) {
  driver.executeScript('browserstack_executor: {"action": "setSessionStatus", "arguments": {"status":"passed","reason": "All Test Passed"}}');
}

/**
 * Mark test as failed
 * @param { webdriver.ThenableWebDriver } driver
 * @param { string } reason
 */
function reportAsFailed(driver, reason) {
  driver.executeScript(`browserstack_executor: {"action": "setSessionStatus", "arguments": {"status":"failed","reason": "${reason}"}}`);
}

/**
 * Run Tests with given webdriver
 * @param { webdriver.ThenableWebDriver } driver
 */
async function execTest(driver) { 
    await driver.get(testedSiteURL);
    // FIXME: Make sure that app has already been launched
    await sleep(8000);
  
    // Test1: App should launch without exception
    {
      const statusElement = await driver.findElement(webdriver.By.css('#status'));
      const statusText = await statusElement.getText();
      const errorString = 'Exception thrown, see JavaScript console';
  
      if (statusText === errorString) {
        reportAsFailed(driver, errorString);
        return;
      }
    }

    reportAsPassed(driver);
}

function main() {
  for (const deviceCapability of deviceCapabilities) {
    let capability = Object.assign(deviceCapability, projectCapability);

    if (capability.device) {
      capability.name = `Test: ${capability.device} ${capability.browserName}`;
    } else {
      capability.name = `Test: ${capability.os} ${capability.os_version}, ${capability.browserName} ${capability.browser_version}`;
    }

    (async function() {
      const driver = new webdriver.Builder().
      usingServer(browserstackURL).
      withCapabilities(capability).
      build();
    
      await execTest(driver);
      await sleep(1000);
      driver.quit();
    })();
  }
}

main(); 
