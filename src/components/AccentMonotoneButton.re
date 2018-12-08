open Styles;
let component = ReasonReact.statelessComponent("AccentMonotoneButton");

let make = (~onClick, ~className=?, children) => {
  ...component,
  render: (_self) =>
    <MaterialUi.ButtonBase
      onClick={(_ev) => onClick()}
    >
    <div className={cn(["bg-accent-100-o72", "br1", className->Cn.unpack])}>
      ...{children}
    </div>
    </MaterialUi.ButtonBase>
}
