const path = require( 'path' );
const webpack = require( 'webpack' );
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
import targets from "./targets";
let LiveReloadPlugin = require('webpack-livereload-plugin');
// let WebpackHookPlugin = require('webpack-hook-plugin');
let exec = require('child_process').exec, child;

const workDir = `/var/www`;
const publicDir = `/resources`;
let command = ``;

console.log(targets);
targets.forEach((obj, i) => {
    if (i !== 0) command += ` && `
    if (!obj.output) obj.output = `index`
    if (typeof obj.useDefaultShell === "undefined") obj.useDefaultShell = false
    if (!obj.command) obj.command = ['']
    if (typeof obj.empp === "undefined") obj.empp = true;
    if (!obj.files) console.error(`ERROR: Files has not be declared in target - ${obj.output}!`)

    command += `${obj.empp ? 'em++' : 'emcc'} ${obj.args ? obj.args.join(' ') : ``} ${obj.files.join(' ')} ${obj.command ? obj.command.join(' ') : ``} `;
    if (obj.useDefaultShell) {
        command += `--shell-file ${workDir}${publicDir}/stub/index.html`;
    }
    command += `-o ${workDir}${publicDir}/wasm/${obj.output}.html `;
});
console.log(command);
exec(command);

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

        // devtool: 'cheap-eval-source-map',

        node: {
            fs: 'empty'
        },

        devtool: 'source-map',

        module: {
            rules: [
                {
                    test: /\.wasm$/,
                    // type: "webassembly/experimental"
                    type: "javascript/auto",
                    loader: "file-loader",
                    // options: {
                    //     publicPath: "dist/"
                    // }
                },
                {
                    test: /\.js$/,
                    use: {
                        loader: 'exports-loader',
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