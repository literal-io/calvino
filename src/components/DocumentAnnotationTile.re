open Styles;
type state = {
  shareButtonRef: ref(option(ReasonReact.reactRef)),
  clipboardInst: ref(option(Clipboard.t)),
};
let component = ReasonReact.reducerComponent("DocumentAnnotationTile");

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
  let handleShareButtonRef = (elem, {ReasonReact.state}) => {
    state.shareButtonRef := Js.Nullable.toOption(elem);
    switch (state.clipboardInst^, state.shareButtonRef^) {
    | (Some(_clipbordInst), _) => /** Already instantiated, noop */ ()
    | (None, Some(shareButtonRef)) =>
      state.clipboardInst :=
        shareButtonRef
        |> ReactDOMRe.findDOMNode
        |> Clipboard.make(
             Clipboard.options(
               ~text=Js.Null_undefined.return(_elem => annotationURL),
               ~container=Js.Null_undefined.undefined,
               ~target=Js.Null_undefined.undefined,
             ),
           )
        |> Js.Option.some
    };
  };
  {
    ...component,
    initialState: () => {
      shareButtonRef: ref(None),
      clipboardInst: ref(None),
    },
    reducer: ((), _state) => ReasonReact.NoUpdate,
    willUnmount: self =>
      switch (self.state.clipboardInst^) {
      | Some(clipboardInst) => Clipboard.destroy(clipboardInst)
      | None => ()
      },
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
              <IconButton
                ref={self.handle(handleShareButtonRef)}
                onClick={ev => {
                  ReactEvent.Mouse.preventDefault(ev);
                  ReactEvent.Mouse.stopPropagation(ev);
                  let _ = onShareClicked();
                  ();
                }}>
                <MaterialIcon.Share style={square(21)} />
              </IconButton>
            </div>
          </a>
        </Card>
      ),
  };
};
