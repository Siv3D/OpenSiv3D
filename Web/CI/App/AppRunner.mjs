import { exec } from 'child_process';
import { argv, exit } from 'process';

const serverProcess = exec("npx statikk --port 8080 --coi");

export function sleep(milliSeconds) {
    return new Promise(resolve => setTimeout(resolve, milliSeconds));
}

async function main() {
	await sleep(5000);
	
	let exitCode = -1;
	const launchedProcess = exec([ "npx", "cdp-gdb-bridge", ...argv ].join(" "));

	try {
		const launchedProcessPromise = new Promise(resolve => {
			let textBuffer = "";
			const exitCondition = /RuntimeExited\((.+)\)/;
		
			launchedProcess.stdout?.on('data', (d) => { 
				textBuffer += d.toString();
		
				const splitText = textBuffer.split("\n");
		
				while (splitText.length > 1) {
					const text = splitText.shift() || "";
					const trimmed = text.trim();
		
					// FIXME
					if (exitCondition.test(trimmed)) {
						exitCode = exitCondition.exec(trimmed)[1];
						resolve();
					}

					console.log(text);
				}
		
				textBuffer = splitText[0];
			});
		});

		await Promise.race([ launchedProcessPromise, sleep(3 * 60 * 1000) ]);
	} finally {
		serverProcess.kill();
		launchedProcess.kill();

		exit(exitCode);
	}
}

main();
