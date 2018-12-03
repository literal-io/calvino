const path = require('path');
const webpack = require('webpack');
const outputDir = path.join(__dirname, 'build/');

const isProd = process.env.NODE_ENV === 'production';
const isClient = process.env.CALVINO_ENV === 'client';

const baseConfig = {
  entry: './src/Index.bs.js',
  devtool: 'source-map',
  mode: isProd ? 'production' : 'development',
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

const nodeConfig = {
  ...baseConfig,
  target: 'node',
  output: {
    path: outputDir,
    publicPath: outputDir,
    filename: 'Index.node.js',
    libraryTarget: 'umd'
  },
  plugins: [
    ...(baseConfig.plugins || []),
    new webpack.DefinePlugin({
      'process.env': {
        'BOOKSHELF_ENV': JSON.stringify('internal'),
        'NODE_ENV': JSON.stringify(process.env.NODE_ENV)
      }
    })
  ]
}

const webConfig = {
  ...baseConfig,
  target: 'web',
  node: {
    fs: "empty"
  },
  output: {
    path: outputDir,
    publicPath: outputDir,
    filename: 'Index.js',
    libraryTarget: 'umd'
  },
  plugins: [
    ...(baseConfig.plugins || []),
    new webpack.DefinePlugin({
      'process.env': {
        'BOOKSHELF_ENV': JSON.stringify('client'),
        'NODE_ENV': JSON.stringify(process.env.NODE_ENV)
      }
    })
  ]
}

module.exports = [webConfig, nodeConfig]
