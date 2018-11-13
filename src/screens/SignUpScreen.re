open Styles;

let component = ReasonReact.statelessComponent("SignUpScreen");

let make = (~renderSignUp, _children) => {
  ...component,
  render: _self =>
    <div
      className={cn(["flex", "flex-auto", "flex-row", "bg-brand", "ff-r"])}>
      <div className={cn(["flex", "flex-1"])}> <RegistrationCTA /> </div>
      <div className={cn(["flex", "flex-1"])}> {renderSignUp()} </div>
    </div>,
};

[@bs.deriving abstract]
type jsProps = {renderSignUp: (. unit) => ReasonReact.reactElement};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(~renderSignUp=() => jsProps->renderSignUpGet(.), [||])
  );
