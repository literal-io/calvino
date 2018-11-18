[@bs.val] external require : string => unit = "require";

require("./static/app.css");
require("tachyons/css/tachyons.css");

let registrationCTAScreen = RegistrationCTAScreen.default;
let signUpScreen = SignUpScreen.default;

let makeClientContext = ContextProvider.makeClientContext;
let makeServerContext = ContextProvider.makeServerContext;
let contextProvider = ContextProvider.default;
