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

module SheetsRegistry = {
  type t;
  [@bs.new] [@bs.module "jss"] external make: unit => t = "SheetsRegistry";
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
