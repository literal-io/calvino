[@bs.val] external require : string => unit = "require";

require("./static/app.css");
require("tachyons/css/tachyons.css");

let registrationCTAScreen = RegistrationCTAScreen.default;
let signUpScreen = SignUpScreen.default;

