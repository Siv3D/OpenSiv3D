import { Key, ThenableWebDriver, until } from "selenium-webdriver";
import test from "mocha";
import parallel, { limit } from "mocha.parallel";
import { use, expect } from "chai";
import { chaiImage } from "chai-image";
import { buildTestCase, Siv3DApp, sleep } from "../util";
import { existsSync, readFileSync, writeFileSync } from "fs";
import { deviceCapabilities, generateCapability, notSupportedDeviceCapabilities } from "../config";
import { ChildProcessWithoutNullStreams, spawn, spawnSync } from "child_process";
import { Local } from "browserstack-local";

limit(3);
use(chaiImage);

const timeout = 2 * 60 * 1000;

parallel("Browserstack Tests", function() {
    this.timeout(timeout);

    deviceCapabilities.forEach(function (cap) {

        const capability = generateCapability(cap);

        let serverProcess: ChildProcessWithoutNullStreams;
        const browserStackLocal = new Local();;

        test.before(async function() {
            spawnSync("./src/TextInput/Build.sh");

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

        test.it(`Supported Device on ${capability.friendlyBrowserName}`, 
            buildTestCase(capability, "Siv3DTest", async function (driver: ThenableWebDriver) {     
                this.timeout(timeout);

                async function FocusToTextInput() {
                    await app.mouseClick(driver.actions(), { x: 200, y: 15 });
                }

                async function GetInputText() {
                    return await driver.executeScript("return Module.GetText()") as string;
                }

                let app: Siv3DApp;
                
                if (capability.os === "iOS") {
                    app = await Siv3DApp.init(
                        driver,
                        "http://bs-local.com:8080/src/TextInput/Siv3DTest.html",
                        { width: 800, height: 600 });
                } else {
                    app = await Siv3DApp.init(
                        driver,
                        "http://127.0.0.1:8080/src/TextInput/Siv3DTest.html",
                        { width: 800, height: 600 });
                }

                await sleep(1000);
    
                await FocusToTextInput();
                await sleep(1000);

                await driver.actions().sendKeys("Siv3D" + Key.ENTER).perform();
                await sleep(3000);

                expect(await GetInputText(), "Characters should be inputted").to.equal("Siv3D");

                await FocusToTextInput();
                await sleep(1000);

                await driver.actions().sendKeys(Key.BACK_SPACE + Key.ENTER).perform();
                await sleep(3000);

                expect(await GetInputText(), "Characters should be deleted.").to.equal("Siv3");
            })
        );
    });

    notSupportedDeviceCapabilities.forEach(function(cap) {

        const capability = generateCapability(cap);

        test.it(`Not supported browser on ${capability.friendlyBrowserName}`, 
            buildTestCase(capability, "Not Supported Browser", async function (driver: ThenableWebDriver) {     
                this.timeout(timeout);

                let app: Siv3DApp;

                if (capability.os === "iOS") {
                    app = await Siv3DApp.init(
                        driver,
                        "http://bs-local.com:8080/src/TextInput/Siv3DTest.html",
                        { width: 800, height: 600 });
                } else {
                    app = await Siv3DApp.init(
                        driver,
                        "http://127.0.0.1:8080/src/TextInput/Siv3DTest.html",
                        { width: 800, height: 600 });
                }
                
                await driver.wait(until.alertIsPresent());
                const alert = await driver.switchTo().alert();
                const alertText = await alert.getText();

                expect(alertText).to.equal("glfwCreateWindow() failed. Your browser seems not to support WebGL 2.0, please enable WebGL 2.0.");

                await alert.accept();
            })
        );
    })
});
