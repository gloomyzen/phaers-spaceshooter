var path = require('path');
var pathToPhaser = path.join(__dirname, '/node_modules/phaser/');
var phaser = path.join(pathToPhaser, 'dist/phaser.js');
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
      { test: /phaser\.js$/, loader: 'expose-loader?Phaser' }
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
      phaser: phaser
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
