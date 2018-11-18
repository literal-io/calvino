/**
 * A simple webpack loader to convert a CSS file to globally scoped JSS-compatible JSON module.
 */

const { cssToJss } = require('jss-cli')

module.exports = function (source) {
  this.value = source
  const jss = cssToJss({ code: source })
  return `module.exports = ${JSON.stringify(jss)}`
}
