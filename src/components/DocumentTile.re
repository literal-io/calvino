open Styles;

let component = ReasonReact.statelessComponent("DocumentTile");

let make = (~title, ~author, ~imageURL, _children) => {
  ...component,
  render: _self =>
    <div
      style={make(~width=px(200), ())}
      className={cn(["flex", "flex-column", "pointer"])}>
      <MaterialUi.Paper
        classes=[MaterialUi.Paper.Classes.Root("overflow-hidden")]>
        {
          switch (imageURL) {
          | Some(imageURL) => <img src=imageURL className={cn(["w-100"])} />
          | None => <div style={make(~height=px(325), ())} />
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
