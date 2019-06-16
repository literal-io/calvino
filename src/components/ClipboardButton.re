type state = {
  clipboardButtonRef: ref(option(ReasonReact.reactRef)),
  clipboardInst: ref(option(Clipboard.t)),
};

let component = ReasonReact.reducerComponent("ClipboardButton");

let onClipboardButtonRef =
    (onGetClipboardText, shareButtonRef, {ReasonReact.state}) => {
  state.clipboardButtonRef := Js.Nullable.toOption(shareButtonRef);
  switch (state.clipboardInst^, state.clipboardButtonRef^) {
  | (Some(_clipboardInst), _) => ()
  | (None, Some(clipboardButtonRef)) =>
    state.clipboardInst :=
      clipboardButtonRef
      |> ReactDOMRe.findDOMNode
      |> Clipboard.make(
           Clipboard.options(
             ~text=Js.Null_undefined.return(_elem => onGetClipboardText()),
             ~target=Js.Null_undefined.undefined,
             ~container=Js.Null_undefined.undefined,
           ),
         )
      |> Js.Option.some
  | _ => ()
  };
};

let make = (~onGetClipboardText, ~render, _children) => {
  ...component,
  initialState: () => {
    clipboardButtonRef: ref(None),
    clipboardInst: ref(None),
  },
  reducer: ((), _state) => ReasonReact.NoUpdate,
  willUnmount: self =>
    switch (self.state.clipboardInst^) {
    | Some(clipboardInst) => Clipboard.destroy(clipboardInst)
    | None => ()
    },
  render: self => {
    let onRef = self.handle(onClipboardButtonRef(onGetClipboardText));
    render(~onRef);
  },
};
