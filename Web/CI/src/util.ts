import { Actions, Builder, By, IRectangle, ThenableWebDriver, until, WebElement } from "selenium-webdriver";
import sharp from "sharp";
import https from "https";
import { Capability } from "./config";
import { Context, Done } from "mocha";
import { ChildProcessWithoutNullStreams, spawn, spawnSync } from "child_process";

/**
 * 
 * @param { number } milliSeconds 
 */
export function sleep(milliSeconds: number) {
    return new Promise(resolve => setTimeout(resolve, milliSeconds));
}

export function spawnAsync(command: string, args: string[]) {
    return new Promise<void>((resolve, reject) => {
        const process = spawn(command, args);

        process.stdout.on('data', chunk => {
            console.log(Buffer.from(chunk).toString());
        });
    
        process.stderr.on('data', chunk => {
            console.error(Buffer.from(chunk).toString());
        });

        process.on('close', code => {
            code ? reject() : resolve();
        });
    });
}

export async function reportAsPassed(driver: ThenableWebDriver) {
    await driver.executeScript('browserstack_executor: {"action": "setSessionStatus", "arguments": {"status":"passed","reason": "Test Case Passed"}}');
}

export async function reportAsFailed(driver: ThenableWebDriver, reason: string) {
    await driver.executeScript(`browserstack_executor: {"action": "setSessionStatus", "arguments": {"status":"failed","reason": "${reason}"}}`);
}

export function buildDriver(caps: Capability) {
    return new Builder()
        .usingServer('https://hub-cloud.browserstack.com/wd/hub')
        .usingHttpAgent(
            new https.Agent({
                keepAlive: true,
                keepAliveMsecs: 30 * 1000
            }))
        .withCapabilities(caps)
        .build();
};

export function buildTestCase(caps: Capability, name: string, testCase: (this: Context, driver: ThenableWebDriver) => Promise<void>): (this: Context, done: Done) => void {
    return function(done: Done) {
        caps.name = name;
        const driver = buildDriver(caps);
        
        testCase.call(this, driver).then(
            async function() {
                await reportAsPassed(driver)
                await driver.quit();
                done();
            },
            async function(e) {
                if (e instanceof Error) {
                    await reportAsFailed(driver, e.message);
                }
                await driver.quit();
                done(e);
            }
        );
    };
};

export interface ISize {
    width: number;
    height: number;
}

export interface IPoint {
    x: number;
    y: number;
}

export class Siv3DApp {

    canvasElement: WebElement;
    canvasRectangle: IRectangle;
    screenSize?: ISize;

    private get canvasSize(): ISize {
        return this.screenSize || { width: this.canvasRectangle.width, height: this.canvasRectangle.height };
    }

    private constructor(canvasElement: WebElement, canvasRectangle: IRectangle, expectedScreenSize?: ISize) {
        this.canvasElement = canvasElement;
        this.canvasRectangle = canvasRectangle;
        this.screenSize = expectedScreenSize;
    }

    private scalePoint(point: IPoint): IPoint {
        point.x += this.canvasRectangle.x;
        point.y += this.canvasRectangle.y;

        if (!this.screenSize) {
            return point;
        }

        const canvasAspectRatio = this.canvasRectangle.height / this.canvasRectangle.width;
        const screenAspectRatio = this.screenSize.height / this.screenSize.width;

        if (canvasAspectRatio > screenAspectRatio) {
            const scale = this.canvasRectangle.width / this.screenSize.width;
            const padding = 0.5 * (this.canvasRectangle.height - this.screenSize.height * scale);

            return {
                x: Math.floor(point.x * scale),
                y: Math.floor(point.y * scale + padding)
            }
        } else {
            const scale = this.canvasRectangle.height / this.screenSize.height;
            const padding = 0.5 * (this.canvasRectangle.width - this.screenSize.width * scale);

            return {
                x: Math.floor(point.x * scale + padding),
                y: Math.floor(point.y * scale)
            }
        }
    }

    static async open(driver: ThenableWebDriver, testedPage: string, expectedScreenSize?: ISize) {   
        await driver.get(testedPage);
        await driver.wait(until.elementLocated(By.id("status")), 30 * 1000);

        const canvas = await driver.findElement(By.css("canvas"));
        return new Siv3DApp(canvas, { x: 0, y: 0, width: 320, height: 240 }, expectedScreenSize);
    }

    async waitForReady(driver: ThenableWebDriver) {
        const statusElement = await driver.findElement(By.id("status"));
        await driver.wait(until.elementTextIs(statusElement, ""))

        this.canvasRectangle = await this.canvasElement.getRect();
    }

    async mouseClick(actions: Actions, point: IPoint) {
        await actions
                .move(this.scalePoint(point))
                .click()
                .pause(30)
                .release()
                .perform();
    }

    async keyDown(actions: Actions, key: string) {
        await actions
                .keyDown(key)
                .pause(30)
                .keyUp(key)
                .perform();
    }

    async screenShot() {
        const imageBuffer = Buffer.from(await this.canvasElement.takeScreenshot(), 'base64');
        return sharp(imageBuffer).resize(this.canvasSize.width, this.canvasSize.height).png().toBuffer();
    }
}
