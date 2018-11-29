open Styles;

let component = ReasonReact.statelessComponent("DocumentTile");

let make = (~title, ~author, ~imageURL=?, ~imageHeight=?, _children) => {
  ...component,
  render: _self =>
    <div
      style={make(~width=px(200), ())}
      className={cn(["flex", "flex-column", "pointer"])}>
      <MaterialUi.Paper
        classes=[MaterialUi.Paper.Classes.Root("overflow-hidden")]>
        {
          switch (imageURL, imageHeight) {
          | (Some(imageURL), None) =>
            <img src=imageURL className={cn(["w-100"])} />
          | (Some(imageURL), Some(imageHeight)) =>
            <img
              src=imageURL
              style={make(~height=px(imageHeight), ())}
              className={cn(["w-100"])}
            />
          | _ => <div style={make(~height=px(325), ())} />
          }
        }
        <div className={cn(["flex", "flex-column", "pa2"])}>
          <span className={cn(["f6", "b", "pd", "mb1"])}>
            {ReasonReact.string(title)}
          </span>
          <span className={cn(["f7", "sd"])}>
            {ReasonReact.string(author)}
          </span>
        </div>
      </MaterialUi.Paper>
    </div>,
};
