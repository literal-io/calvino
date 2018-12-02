const path = require('path');
const outputDir = path.join(__dirname, 'build/');

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './src/Index.bs.js',
  devtool: 'source-map',
  mode: isProd ? 'production' : 'development',
  target: 'node',
  output: {
    path: outputDir,
    publicPath: outputDir,
    filename: 'Index.js',
    libraryTarget: 'umd'
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
        use: [
          require.resolve('./scripts/jss-loader'),
          'extract-loader',
          'css-loader'
        ]
      },
      {
        test: /@javamonn/,
        use: [
          {
            loader: 'babel-loader',
            options: {
              presets: ['@babel/preset-env'],
              plugins: ['@babel/plugin-transform-flow-strip-types']
            }
          }
        ]
      }
    ]
  }
};
