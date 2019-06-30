open Styles;
let component = ReasonReact.statelessComponent("DocumentAnnotationTile");

let make =
    (
      ~text,
      ~title,
      ~author,
      ~onShareClicked,
      ~annotationURL,
      ~onClick=?,
      ~hideDocumentInfo=?,
      _children,
    ) => {
  {
    ...component,
    render: self =>
      MaterialUi.(
        <Card>
          <a
            onClick=?{
              switch (onClick) {
              | Some(onClick) =>
                let handleClick = ev => {
                  ReactEvent.Mouse.preventDefault(ev);
                  if (!ReactEvent.Mouse.isPropagationStopped(ev)) {
                    onClick(annotationURL);
                  };
                };
                Some(handleClick);
              | None => None
              }
            }
            className={cn(["no-underline"])}
            href=annotationURL>
            <div className={cn(["mh3"])}> <HighlightText text /> </div>
            <div
              className={cn([
                "flex",
                "flex-row",
                "justify-between",
                "items-center",
                "mh3",
                "mv1",
              ])}>
              <div className={cn(["flex", "flex-column"])}>
                {switch (hideDocumentInfo) {
                 | None
                 | Some(false) =>
                   <>
                     <span className={cn(["f7", "pd"])}>
                       {ReasonReact.string(title)}
                     </span>
                     <span className={cn(["f7", "sd"])}>
                       {ReasonReact.string(author)}
                     </span>
                   </>
                 | Some(true) => ReasonReact.null
                 }}
              </div>
              <ClipboardButton
                onGetClipboardText={() => annotationURL}
                render={(~onRef) =>
                  <IconButton
                    ref=onRef
                    onClick={ev => {
                      ReactEvent.Mouse.preventDefault(ev);
                      ReactEvent.Mouse.stopPropagation(ev);
                      let _ = onShareClicked();
                      ();
                    }}>
                    <MaterialIcon.Share style={square(21)} />
                  </IconButton>
                }
              />
            </div>
          </a>
        </Card>
      ),
  };
};
