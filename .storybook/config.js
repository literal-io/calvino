import { configure } from "@storybook/react"

configure(() => {
  require("typeface-roboto");

  require('../src/__stories__/ComponentStory.bs.js')
  require('../src/__stories__/ScreenStory.bs.js')
  require('../src/__stories__/ListsStory.bs.js')
}, module)

