const mix = require('laravel-mix');
let LiveReloadPlugin = require('webpack-livereload-plugin');
let WebpackHookPlugin = require('webpack-hook-plugin');
// let img = require('file.png');
const path = require('path');

let files = ["canvas.c"];

let plugins = [];
plugins.push(new LiveReloadPlugin())
plugins.push(new WebpackHookPlugin({
    onBuildStart: ['prepare_project ' + files.join(' ')],
    // onBuildEnd: ['prepare_project ' + files.join(' ')],
    onCompile: ['prepare_project ' + files.join(' ')],
}));

mix.js('resources/js/test.js', 'public/js/main.js')
    .sass('resources/sass/app.scss','public/css')
    .copy('resources/img', 'public/img')
    .webpackConfig({
        module: {
            rules: [
                {
                    test: /\.c$/,
                    use: ['cache-loader'],
                    include: path.resolve('src'),
                },
                /*{
                    test: /\.c/,
                    type: 'webassembly/experimental'
                },
                {
                    test: /\.cpp$/,
                    type: 'webassembly/experimental'
                },
                {
                    test: /\.h/,
                    type: 'webassembly/experimental'
                },
                {
                    test: /\.hpp/,
                    type: 'webassembly/experimental'
                }*/
            ]
        },
        watch: true,
        plugins: plugins
    }).sourceMaps()
    .version();