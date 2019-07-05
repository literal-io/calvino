import {configure} from '@storybook/react';

configure(() => {
  require('typeface-roboto');
  require('typeface-roboto-slab');

  require('../__stories__/ComponentStory.bs.js');
  require('../__stories__/ScreenStory.bs.js');
  require('../__stories__/ExtensionBrowserActionMenuStory.bs.js');
  require('../__stories__/DocumentDetailStory.bs.js');
}, module);
