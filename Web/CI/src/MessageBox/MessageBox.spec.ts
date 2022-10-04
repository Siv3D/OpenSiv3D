import { Key, ThenableWebDriver, until } from "selenium-webdriver";
import test from "mocha";
import parallel, { limit } from "mocha.parallel";
import { use, expect } from "chai";
import { chaiImage } from "chai-image";
import { buildTestCase, getUrl, Siv3DApp, sleep, spawnAsync } from "../util";
import { existsSync, readFileSync, writeFileSync } from "fs";
import { deviceCapabilities, generateCapability, notSupportedDeviceCapabilities } from "../config";
import { ChildProcessWithoutNullStreams, spawn, spawnSync } from "child_process";
import { Local } from "browserstack-local";

limit(5);
use(chaiImage);

const timeout = 2 * 60 * 1000;

parallel("MessageBox Tests", function() {
    this.timeout(timeout);

    deviceCapabilities.forEach(function (cap) {

        const capability = generateCapability(cap);

        let serverProcess: ChildProcessWithoutNullStreams;
        const browserStackLocal = new Local();;

        test.before(async function() {
            await spawnAsync("./src/MessageBox/Build.sh", []);

            await new Promise<Error | undefined>(resolve => {
                browserStackLocal.start({
                    key: process.env.BROWSERSTACK_ACCESS_KEY
                }, resolve);
            });

            serverProcess = spawn("npx", ["http-server"]);
            
            await sleep(5000);
        })

        test.after(async function() {
            serverProcess.kill();

            await new Promise<void>(resolve => {
                browserStackLocal.stop(resolve);
            });
        })

        test.it(`MessageBox on ${capability.friendlyBrowserName}`, 
            buildTestCase(capability, "MessageBox", async function (driver: ThenableWebDriver) {     
                this.timeout(timeout);

                async function GetResult() {
                    return await driver.executeScript("return Module[\"_GetResult\"]()") as string;
                }

                const app = await Siv3DApp.open(
                    driver,
                    getUrl(capability, "src/MessageBox/Siv3DApp.html"),
                    capability,
                    { width: 800, height: 600 });
               
                await app.waitForReady(driver);

                {
                    await driver.wait(until.alertIsPresent());
                    const alert = await driver.switchTo().alert();
                    const alertText = await alert.getText();

                    expect(alertText).to.equal("Normal MessageBox");
                    await alert.accept()
                    expect(await GetResult()).to.equal(0);
                }

                {
                    await driver.wait(until.alertIsPresent());
                    const alert = await driver.switchTo().alert();
                    const alertText = await alert.getText();

                    expect(alertText).to.equal("OK or Cancel MessageBox");
                    await alert.accept()
                    expect(await GetResult()).to.equal(0);
                }

                {
                    await driver.wait(until.alertIsPresent());
                    const alert = await driver.switchTo().alert();
                    const alertText = await alert.getText();

                    expect(alertText).to.equal("OK or Cancel MessageBox");
                    await alert.dismiss()
                    expect(await GetResult()).to.equal(1);
                }
            })
        );
    });
});
