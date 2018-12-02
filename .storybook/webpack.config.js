const path = require('path')

module.exports = (baseConfig, env, defaultConfig) => {

  // Include our node_modules when resolving out of directory packages (i.e. linked packages) 
  // due to module duplication issues with BuckleScript.
  const resolveModules = (defaultConfig.resolve.modules || [])
  resolveModules.push(path.resolve(__dirname, '../node_modules'))
  defaultConfig.resolve.modules = resolveModules

  // Run unbuilt dependencies through babel.
  defaultConfig.module.rules.push({
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
  })

  return defaultConfig
}
