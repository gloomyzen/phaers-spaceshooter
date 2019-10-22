var path = require('path');
var pathToPhaser = path.join(__dirname, '/node_modules/phaser/');
var phaser = path.join(pathToPhaser, 'dist/phaser.js');
var pathToPhaserDebugDraw = path.join(__dirname, '/node_modules/phaser-plugin-debug-draw/');
var DebugDrawPlugin = path.join(pathToPhaserDebugDraw, 'dist/PhaserDebugDrawPlugin.esm.js');
var LiveReloadPlugin = require('webpack-livereload-plugin');

module.exports = {
  mode: 'development',
  entry: './src/boilerplate/game.ts',
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bundle.js',
  },
  module: {
    rules: [
      { test: /\.ts$/, loader: 'ts-loader', exclude: '/node_modules/' },
      { test: /phaser\.js$/, loader: 'expose-loader?Phaser' },
      { test: /PhaserDebugDrawPlugin.esm\.js$/, loader: 'expose-loader?DebugDrawPlugin' }
    ]
  },
  // devServer: {
  //   contentBase: path.resolve(__dirname, './'),
  //   publicPath: '/dist/',
  //   host: '127.0.0.1',
  //   port: 8080,
  //   open: true
  // },
  resolve: {
    extensions: ['.ts', '.js'],
    alias: {
      phaser: phaser,
      DebugDrawPlugin: DebugDrawPlugin
    }
  },
  plugins: [
    new LiveReloadPlugin()
  ],
  watchOptions: {
    poll: true
  },
  performance: { hints: false },
  devtool: 'source-map'
};
