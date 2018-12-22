open Styles;
let component = ReasonReact.statelessComponent("Spacer");

let make = (~size, _children) => {
  ...component,
  render: _self => <div className={cn(["ma" ++ string_of_int(size)])} />,
};
