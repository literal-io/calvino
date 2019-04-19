[@bs.val] external requireJSS: string => Js.Json.t = "require";

module SheetsManager = {
  /* FIXME: There might be a better way to type this, builtin JS Map(...) type */
  type t;
  [@bs.new] external make: unit => t = "Map";
};

module GenerateClassName = {
  type t;
  [@bs.val] [@bs.module "@material-ui/core/styles"]
  external make: unit => t = "createGenerateClassName";
};

module StyleSheet = {
  type t;
  [@bs.scope "default"] [@bs.module "react-jss/lib/jss"]
  external make: Js.Json.t => t = "createStyleSheet";

  [@bs.send] external attach: t => t = "";
};

module SheetsRegistry = {
  type t;
  [@bs.new] [@bs.module "react-jss/lib/jss"] external make: unit => t = "SheetsRegistry";

  [@bs.send.pipe: t] external add: StyleSheet.t => unit = "";
};

module JssProvider = {
  [@bs.deriving abstract]
  type jsProps = {
    registry: Js.nullable(SheetsRegistry.t),
    generateClassName: GenerateClassName.t,
  };
  [@bs.val] [@bs.module "react-jss/lib/JssProvider"]
  external jssProviderReactClass: ReasonReact.reactClass = "default";

  let make = (~registry=?, ~generateClassName, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=jssProviderReactClass,
      ~props=
        jsProps(
          ~registry=Js.Nullable.fromOption(registry),
          ~generateClassName,
        ),
      children,
    );
};
