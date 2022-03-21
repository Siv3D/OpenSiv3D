declare module "mocha.parallel" {

    export default function parallel(name: string, fn: (this: import("mocha").Context) => void): void;

    export function limit(n: number): void;
}