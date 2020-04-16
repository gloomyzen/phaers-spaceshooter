/**
 * emcc ${str} --shell-file ${WORK_DIR}/resources/stub/index.html --emrun -o ${WORK_DIR}${PUBLIC_DIR}/wasm/index.wasm
 * Setting targets for project build
 * @type {{output: string, args: [string], files: [string], command: [string]}[]}
 */
export default [
    /*{
        files: ['src/examples/canvas.c'], //Files for compilation
        output: 'canvas', // Output name
        args: ['-s WASM=1'], //Arguments for emscripten
        command: [''], // Extra command like --emrun
    },*/
    /*{
        files: ['src/examples/fibonacci.c'],
        output: 'fibonacci',
        args: [`-O3` , `-s WASM=1`, `-s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'`, `-s ALLOW_MEMORY_GROWTH=1`, `-s MODULARIZE=1`, `-s 'EXPORT_NAME="fibonacci"'`],
        command: [''],
    },*/
    /*{
        files: ['src/examples/usesdl.c'],
        output: 'sdl',
        outputPath: ``,
        args: [`-O3` , `-s WASM=1`, `-s USE_SDL=2`, `-s USE_SDL_TTF=2`, `--preload-file /var/www/resources/font`],
        command: [''],
    },*/
    /*{
        files: ['src/examples/sprite.c'],
        output: 'sdl',
        outputPath: ``,
        args: [`-O3` , `-s WASM=1`, `-s USE_SDL=2`, `-s USE_SDL_IMAGE=2`, `-s SDL2_IMAGE_FORMATS=["png"]`, `--preload-file /var/www/resources/sprites`],
        command: [''],
    },*/
    {
        files: ['src/examples/sprite_animation.c'],
        output: 'sprite',
        outputPath: ``,
        args: [`-O3` , `-s WASM=1`, `-s USE_SDL=2`, `-s USE_SDL_IMAGE=2`, `-s SDL2_IMAGE_FORMATS=["png"]`, `--preload-file /var/www/resources/sprites`],
        command: [''],
    }
];