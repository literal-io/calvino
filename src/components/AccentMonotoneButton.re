open Styles;
let component = ReasonReact.statelessComponent("AccentMonotoneButton");

let make = (~href=?, ~className=?, ~contentClassName=?, children) => {
  ...component,
  render: _self =>
    ReasonReact.cloneElement(
      <MaterialUi.ButtonBase
        classes=[Root(cn([className->Cn.unpack]))]>
        <MaterialUi.Paper
          classes=[
            Root(
              cn(["bg-accent-100-o60", "br1", contentClassName->Cn.unpack]),
            ),
          ]>
          ...children
        </MaterialUi.Paper>
      </MaterialUi.ButtonBase>,
      ~props=
        switch (href) {
        | Some(href) => {"href": href}
        | None => Js.Obj.empty()
        },
      [||],
    ),
};
