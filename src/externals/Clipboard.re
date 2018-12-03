type t;


[@bs.deriving abstract]
type options = {
  container: Js.Null_undefined.t(Dom.element),
  text: Js.Null_undefined.t(Dom.element => string),
  target: Js.Null_undefined.t(Dom.element => string),
};

[@bs.new] [@bs.module]
external make : (Dom.element, options) => t = "clipboard";

[@bs.send] external destroy : t => unit = "";

let make = (options, elem) => make(elem, options);
