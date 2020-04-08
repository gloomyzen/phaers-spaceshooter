const path = require( 'path' );
const webpack = require( 'webpack' );
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
let LiveReloadPlugin = require('webpack-livereload-plugin');
let WebpackHookPlugin = require('webpack-hook-plugin');

let files = ["canvas.c"];

let plugins = [];
plugins.push(new LiveReloadPlugin())
plugins.push(new WebpackHookPlugin({
    onBuildStart: ['prepare_project ' + files.join(' ')],
    // onBuildEnd: ['prepare_project ' + files.join(' ')],
    onCompile: ['prepare_project ' + files.join(' ')],
}));
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