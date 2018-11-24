[@bs.val] external require : string => unit = "require";

require("./static/app.css");
require("tachyons/css/tachyons.css");

/** Screens */
let registrationCTAScreen = RegistrationCTAScreen.default;
let signUpScreen = SignUpScreen.default;

/** Components */
let infiniteList = InfiniteList.default;
let highlightListItem = HighlightListItem.default;
let sectionList = SectionList.default;

let makeClientContext = ContextProvider.makeClientContext;
let makeServerContext = ContextProvider.makeServerContext;
let contextProvider = ContextProvider.default;
