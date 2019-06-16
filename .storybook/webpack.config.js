const path = require('path')

module.exports = (baseConfig, env, defaultConfig) => {

  // Include our node_modules when resolving out of directory packages (i.e. linked packages) 
  // due to module duplication issues with BuckleScript.
  const resolveModules = (defaultConfig.resolve.modules || [])
  resolveModules.push(path.resolve(__dirname, '../node_modules'))
  defaultConfig.resolve.modules = resolveModules

  // Run unbuilt dependencies through babel.
  defaultConfig.module.rules.push({
    test: /\.(js|jsx)$/,
    include: [
      /\/javamonn\//,
      /\/librarian\//,
    ],
    use: [
      {
        loader: 'babel-loader',
        options: {
          presets: ['@babel/preset-env'],
          plugins: ['@babel/plugin-transform-flow-strip-types']
        }
      }
    ]
  })

  defaultConfig.target = 'web'
  defaultConfig.node = (defaultConfig.node || {})
  defaultConfig.node.fs = 'empty'

  return defaultConfig
}
