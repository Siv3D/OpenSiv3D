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

parallel("TextInput Tests", function() {
    this.timeout(timeout);

    deviceCapabilities.forEach(function (cap) {

        const capability = generateCapability(cap);

        let serverProcess: ChildProcessWithoutNullStreams;
        const browserStackLocal = new Local();;

        test.before(async function() {
            await spawnAsync("./src/TextInput/Build.sh", []);

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

        test.it(`TextInput on ${capability.friendlyBrowserName}`, 
            buildTestCase(capability, "TextInput", async function (driver: ThenableWebDriver) {     
                this.timeout(timeout);

                async function FocusToTextInput() {
                    await app.mouseClick(driver.actions(), { x: 200, y: 15 });
                }

                async function GetInputText() {
                    return await driver.executeScript("return Module[\"_GetResult\"]()") as string;
                }

                const app: Siv3DApp = await Siv3DApp.open(
                    driver,
                    getUrl(capability, "src/TextInput/Siv3DApp.html"),
                    capability,
                    { width: 800, height: 600 });

                await app.waitForReady(driver);
                await sleep(1000);
    
                await FocusToTextInput();
                await sleep(1000);
                
                await app.sendKeys(driver, "Siv3D" + Key.ENTER);
                await sleep(2000);
                await FocusToTextInput();
                await sleep(1000);

                if (!(capability.os == "android" && capability.device == "Google Pixel 6")) {
                    expect(await GetInputText(), "Characters should be inputted").to.equal("Siv3D");
                } else {
                    await GetInputText();
                }

                await FocusToTextInput();
                await sleep(1000);
                
                await app.sendKeys(driver, Key.BACK_SPACE + Key.ENTER);
                await sleep(2000);
                await FocusToTextInput();
                await sleep(1000);
                
                if (capability.os !== "iOS" && !(capability.os == "android" && capability.device == "Google Pixel 6")) {
                    expect(await GetInputText(), "Characters should be deleted.").to.equal("Siv3");
                } else {
                    await GetInputText();
                }

                await FocusToTextInput();
                await sleep(1000);

                await app.sendKeys(driver, Key.ARROW_LEFT + "2" + Key.ARROW_RIGHT + "K" + Key.ENTER);
                await sleep(2000);
                await FocusToTextInput();
                await sleep(1000);

                if (capability.os !== "iOS" && !(capability.os == "android" && capability.device == "Google Pixel 6")) {
                    expect(await GetInputText(), "Characters should be inputted").to.equal("Siv23K");
                } else {
                    await GetInputText();
                }
            })
        );
    });
});
