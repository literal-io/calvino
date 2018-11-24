open Styles;
let component = ReasonReact.statelessComponent("HighlightListItem");

let make = (~text, ~title, ~author, ~onShareClicked, _children) => {
  ...component,
  render: _self =>
    MaterialUi.(
      <Card>
        <CardContent> <HighlightText text /> </CardContent>
        <div
          className={
            cn(["flex", "flex-row", "justify-between", "items-center"])
          }>
          <div className={cn(["flex", "flex-column", "ml3"])}>
            <span className={cn(["b", "f6", "pd"])}>
              {ReasonReact.string(title)}
            </span>
            <span className={cn(["f6", "sd"])}>
              {ReasonReact.string(author)}
            </span>
          </div>
          <CardActions>
            <IconButton onClick={_ev => onShareClicked()}>
              <MaterialIcon.Share />
            </IconButton>
          </CardActions>
        </div>
      </Card>
    ),
};

[@bs.deriving abstract]
type jsProps = {
  text: string,
  title: string,
  author: string,
  onShareClicked: (. unit) => unit,
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~text=jsProps->textGet,
      ~title=jsProps->titleGet,
      ~author=jsProps->authorGet,
      ~onShareClicked=() => jsProps->onShareClickedGet(.),
      [||],
    )
  );
