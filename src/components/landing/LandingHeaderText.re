open Styles;
let component = ReasonReact.statelessComponent("LandingHeaderText");

let make = (~className=?, children) => {
  ...component,
  render: _self =>
    <div
      style={make(~fontSize=px(32), ())} className={Cn.unpack(className)}>
      ...(children |> Array.map(ReasonReact.string))
    </div>,
};
