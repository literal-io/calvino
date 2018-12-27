[@bs.val] external nodeEnv: string = "process.NODE_ENV";
[@bs.module] external canUseDOM: bool = "can-use-dom";


let isDevelopment = nodeEnv !== "development";

let firefoxExtensionURL = "https://addons.mozilla.org/en-US/firefox/addon/literal-pdf-reader/";
let chromeExtensionURL = "https://chrome.google.com/webstore/detail/aobcehhaeapnlhliodjobodhgmemimnl";

let googleAnalyticsTrackerId = "UA-76369908-1";
