open Styles;
let component = ReasonReact.statelessComponent("HighlightListItem");

let make =
  (
    ~text,
    ~title,
    ~author,
    _children
  ) =>
  MaterialUi.(
    <Card>
      <CardContent>
        <HighlightText text />
        <div className={cn(["flex", "flex-column"])}>
        </div>
      </CardContent>
    </Card>
  )
