open Styles;
let component = ReasonReact.statelessComponent("IconListItem");

let make =
    (
      ~icon,
      ~title,
      ~description,
      ~titleClassName=?,
      ~descriptionClassName=?,
      ~className=?,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div
      className={
        cn(["flex", "flex-row", "items-center", Cn.unpack(className)])
      }>
      <div className={cn(["mr3"])}> icon </div>
      <div className={cn(["flex", "flex-column"])}>
        <span className={Cn.unpack(titleClassName)}>
          {ReasonReact.string(title)}
        </span>
        <span className={Cn.unpack(descriptionClassName)}>
          {ReasonReact.string(description)}
        </span>
      </div>
    </div>,
};
