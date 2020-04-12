import fibonacci from '../../wasm/fibonacci.js';
import fibonacciModule from '../../wasm/fibonacci.wasm';

export function runFibonacci() {
    const module = fibonacci({
        locateFile(path) {
            if(path.endsWith('.wasm')) {
                return fibonacciModule;
            }
            return path;
        }
    });


    module.onRuntimeInitialized = () => {
        console.log(module._fib(33));
    };
}