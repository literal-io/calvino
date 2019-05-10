import {configure} from '@storybook/react';

configure(() => {
  require('typeface-roboto');
  require('typeface-roboto-slab');

  require('../src/__stories__/ComponentStory.bs.js');
  require('../src/__stories__/ScreenStory.bs.js');
  require('../src/__stories__/ExtensionBrowserActionMenuStory.bs.js');
}, module);
