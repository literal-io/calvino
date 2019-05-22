[@bs.val] external require: string => unit = "require";

require("./static/app.css");
require("tachyons/css/tachyons.css");

/** Browser Action Menu */
let registrationCTAScreen = RegistrationCTAScreen.default;
let browserActionMenuDashboardLibrary = BrowserActionMenuDashboardLibrary.default;

let documentAnnotationsList = DocumentAnnotationsList.default;

let signUpScreen = SignUpScreen.default;
let dashboardScreen = DashboardScreen.default;
let landingScreen = LandingScreen.default;

/** Components */
let infiniteList = InfiniteList.default;
let sectionList = SectionList.default;

let makeClientContext = ContextProvider.makeClientContext;
let makeServerContext = ContextProvider.makeServerContext;
let contextProvider = ContextProvider.default;
