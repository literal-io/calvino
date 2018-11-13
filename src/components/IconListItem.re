open Styles;
let component = ReasonReact.statelessComponent("IconListItem");

let make =
    (
      ~icon,
      ~title,
      ~description,
      ~titleClassName,
      ~descriptionClassName,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div className={cn(["flex", "flex-row", "items-center"])}>
      <div className={cn(["mr3"])}> icon </div>
      <div className={cn(["flex", "flex-column"])}>
        <span className={titleClassName}>
          {ReasonReact.string(title)}
        </span>
        <span className={descriptionClassName}>
          {ReasonReact.string(description)}
        </span>
      </div>
    </div>,
};
