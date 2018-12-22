type t;

[@bs.deriving abstract]
type navigator = {userAgent: string};

external asNavigator: Webapi.Dom.Window.navigator => navigator = "%identity";

[@bs.deriving abstract]
type browser = {
  name: string,
  version: string,
};

[@bs.val] [@bs.module "bowser"] external make: string => t = "getParser";

[@bs.send] external getBrowser: t => browser = "";
