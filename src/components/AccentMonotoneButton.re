open Styles;
let component = ReasonReact.statelessComponent("AccentMonotoneButton");

let make = (~onClick, ~className=?, ~contentClassName=?, children) => {
  ...component,
  render: _self =>
    <MaterialUi.ButtonBase
      onClick={_ev => onClick()} classes=[Root(cn([className->Cn.unpack]))]>
      <MaterialUi.Paper
        classes=[
          Root(
            cn(["bg-accent-100-o60", "br1", contentClassName->Cn.unpack]),
          ),
        ]>
        ...children
      </MaterialUi.Paper>
    </MaterialUi.ButtonBase>,
};
