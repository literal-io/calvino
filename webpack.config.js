const path = require('path');
const outputDir = path.join(__dirname, 'build/');

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './src/Index.bs.js',
  devtool: 'hidden-source-map',
  mode: isProd ? 'production' : 'development',
  output: {
    path: outputDir,
    publicPath: outputDir,
    filename: 'Index.js',
    libraryTarget: 'umd',
    library: 'calvino'
  },
  devServer: {
    compress: true,
    contentBase: outputDir,
    port: process.env.PORT || 8000,
    historyApiFallback: true
  },
  module: {
    rules: [
      {
        test: /\.css$/,
        use: [ 'style-loader', 'css-loader' ]
      }
    ]
  }
};
