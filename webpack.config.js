const path = require( 'path' );
const webpack = require( 'webpack' );
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
let LiveReloadPlugin = require('webpack-livereload-plugin');
// let WebpackHookPlugin = require('webpack-hook-plugin');
let exec = require('child_process').exec, child;

/**
 * Setting targets for project build
 * @type {({files: [string], target: string}|{files: [string], target: string}|{files: [string], target: string})[]}
 */
const targets = [
    {
    target: "canvas",
    files: ['src/canvas.c']
    },
    {
        target: "canvas2",
        files: ['src/canvas.c']
    },
    {
        target: "canvas3",
        files: ['src/canvas.c']
    }
];
let command = 'prepare_project clear';

targets.forEach((obj, i) => {
    command += ` && `;
    command += `prepare_project target ${obj.target} ${obj.files.join(' ')}`;
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
        entry: './resources/js/game.js',

        output: {
            path: path.resolve( __dirname, 'public' ),
            filename: 'index.js',
        },

        devtool: 'cheap-eval-source-map',

        module: {
            rules: [
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

        plugins: plugins

    }
};
