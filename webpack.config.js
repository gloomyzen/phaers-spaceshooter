const path = require( 'path' );
const webpack = require( 'webpack' );
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
let LiveReloadPlugin = require('webpack-livereload-plugin');
// let WebpackHookPlugin = require('webpack-hook-plugin');
let exec = require('child_process').exec, child;

/**
 * emcc ${str} --shell-file ${WORK_DIR}/resources/stub/index.html --emrun -o ${WORK_DIR}${PUBLIC_DIR}/wasm/index.wasm
 * Setting targets for project build
 * @type {{output: string, args: [string], files: [string], command: [string]}[]}
 */
const targets = [
    {
        files: ['src/canvas.c'], //Files for compilation
        output: 'canvas', // Output name
        args: ['-s WASM=1'], //Arguments for emscripten
        command: ['--emrun'], // Extra command
    }
];
const workDir = `/var/www`;
const publicDir = `/resources`;
let command = ``;

targets.forEach((obj, i) => {
    if (i !== 0) command += ` && `
    if (!obj.output) obj.output = `index`
    if (!obj.command) obj.command = ['']
    if (!obj.files) console.error(`ERROR: Files has not be declared in target - ${obj.output}!`)

     command += `emcc ${obj.files.join(' ')} ${obj.args ? obj.args.join(' ') : ``} ${obj.command ? obj.command.join(' ') : ``} `
         + `--shell-file ${workDir}${publicDir}/stub/index.html -o ${workDir}${publicDir}/wasm/${obj.output}`;
});
console.log(command);
// exec(command);

/**
 * @type {*[]}
 */
let plugins = [];
plugins.push(new LiveReloadPlugin())
/*plugins.push(new WebpackHookPlugin({
    onBuildStart: [command],
    // onBuildEnd: [command],
    // onCompile: [command],
}));*/
plugins.push(new MiniCssExtractPlugin({
    filename: 'style.css',
    chunkFilename: '[id].css'
}));

module.exports = ( env, options ) => {
    return {
        mode: "development",
        context: path.resolve(__dirname, "."),
        entry: './resources/js/game.js',

        output: {
            path: path.resolve( __dirname, 'public' ),
            filename: 'index.js',
        },

        devtool: 'cheap-eval-source-map',

        module: {
            rules: [
                {
                    test: /\.wasm$/,
                    type: "webassembly/experimental"
                },
                {
                    test: /\.js$/,
                    use: {
                        loader: 'babel-loader'
                    },
                    exclude: /(node_modules|bower_components)/
                },
                {
                    test: /\.css$/,
                    use: [
                        MiniCssExtractPlugin.loader,
                        {
                            loader: 'css-loader',
                            options: {
                                importLoaders: 1,
                                minimize: ( options.mode == 'production' ? true : false ),
                                sourceMap: true,
                            }
                        },
                        {
                            loader: 'postcss-loader',
                            options: {
                                plugins: [ require( 'autoprefixer' ) ]
                            }
                        },
                    ],
                },
                {
                    test: /\.(png|jpg|gif)$/,
                    use: [
                        {
                            loader: 'file-loader',
                            options: {
                                name: '[name].[ext]',
                                outputPath: 'images/'
                            }
                        }
                    ]
                },
            ],
        },

        // optimization: {
        //     chunkIds: "deterministic" // To keep filename consistent between different modes (for example building only)
        // },
        // experiments: {
        //     asyncWebAssembly: true,
        //     importAwait: true
        // },

        plugins: plugins

    }
};
