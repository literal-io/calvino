import { configure } from "@storybook/react"

configure(() => {
  require('../src/Index.bs.js')
  require('../src/__stories__/ComponentStory.bs.js')
  require('../src/__stories__/ScreenStory.bs.js')
}, module)

