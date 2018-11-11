import { configure } from "@storybook/react"

configure(() => {
  require("../src/static/app.css");
  require("typeface-roboto");
  require("tachyons/css/tachyons.css");

  require('../src/__stories__/ComponentStory.bs.js')
  require('../src/__stories__/ScreenStory.bs.js')
}, module)

