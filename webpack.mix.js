const mix = require('laravel-mix');
let LiveReloadPlugin = require('webpack-livereload-plugin');

mix.js('resources/js/test.js', 'public/js/main.js')
    .sass('resources/sass/app.scss','public/css')
    .copy('resources/img', 'public/img')
    .webpackConfig({
        plugins: [
            new LiveReloadPlugin()
        ]
    }).sourceMaps()
    .version();