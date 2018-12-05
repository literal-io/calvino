open Styles;

type state = {clampedText: option(string)};

let maxLinesCount = 6.0;

type actions =
  | SetClampedText(string);

let component = ReasonReact.reducerComponent("HighlightText");

let getElemHeight = (elem) => {
  let rect = Webapi.Dom.Element.getBoundingClientRect(elem);
  float_of_int(Webapi.Dom.DomRect.(bottom(rect) - top(rect)));
}


let onTextRef = (textRef, {ReasonReact.state}) => {
  switch (Js.Nullable.toOption(textRef)) {
    | Some(textRef) when Js.Option.isNone(state.clampedText) =>
      let elemLineHeightPx = (
        Webapi.Dom.(
          window
          |> Window.getComputedStyle(textRef)
          |> CssStyleDeclaration.getPropertyValue("line-height")
        )
      );
      let elemLineHeight = (
        elemLineHeightPx
        |> Js.String.substring(
            ~from=0,
            ~to_=Js.String.length(elemLineHeightPx) - 2
          )
        |> float_of_string
      );
      let maxHeight = elemLineHeight *. maxLinesCount;
      let _ = while (maxHeight < getElemHeight(textRef)) {
        let _ = Webapi.Dom.(
          textRef
          |. Element.setTextContent(
              textRef
              |> Element.textContent
              |> Js.String.replaceByRe(
                  [%re "/\\W*\\s(\\S)*$/"],
                  {j|…|j}
                )
            )
        );
      }
    | _ => ()
  }
}

let make = (~text, _children) => {
  ...component,
  initialState: () => {clampedText: None},
  reducer: (action, _state) =>
    switch (action) {
    | SetClampedText(text) =>
      ReasonReact.Update({clampedText: Some(text)})
    },
  render: self =>
    <div
      className={
        cn([
          "flex",
          "flex-auto",
          "bg-white",
          "items-center",
          "justify-center",
        ])
      }>
      <p>
        <span
          ref={self.handle(onTextRef)}
          style={lineHeight(rem(1.43)) +++ bgaAccent(0.24)}
          className={cn(["ff-rs", "f7", "pd", "fw5"])}>
          {
            ReasonReact.string(
              switch (self.state.clampedText) {
              | Some(clampedText) => clampedText
              | None => text
              },
            )
          }
        </span>
      </p>
    </div>,
};
