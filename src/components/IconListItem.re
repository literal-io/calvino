open Styles;
let component = ReasonReact.statelessComponent("IconListItem");

let make = (~icon, ~title, ~description, _children) => {
  ...component,
  render: _self =>
    <div className={cn(["flex", "flex-row", "items-center"])}>
      <div className={cn(["mr3"])}>
        {icon}
      </div>
      <div className={cn(["flex", "flex-column"])}>
        <span className={cn(["f7", "pl", "b", "mb1"])}>{ReasonReact.string(title)}</span>
        <span className={cn(["f7", "sl"])}>{ReasonReact.string(description)}</span>
      </div>
    </div>
}
