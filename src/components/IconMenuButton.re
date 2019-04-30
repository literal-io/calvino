type action =
  | SetAnchorElement(option(Dom.element));

type state = {anchorElement: option(Dom.element)};

let component = ReasonReact.reducerComponent("IconMenuButton");

external unsafeAsDomElement: Js.t({..}) => Dom.element = "%identity";

let make = (~renderMenuItems, ~renderIcon, _children) => {
  ...component,
  initialState: () => {anchorElement: None},
  reducer: (action, _state) =>
    switch (action) {
    | SetAnchorElement(el) => ReasonReact.Update({anchorElement: el})
    },
  render: self => {
    let handleClick = ev =>
      ev
      |> ReactEvent.Mouse.currentTarget
      |> unsafeAsDomElement
      |> (elem => self.send(SetAnchorElement(Some(elem))));
    let handleClose = () => {
      self.send(SetAnchorElement(None));
      ();
    };
    <>
      <MaterialUi.IconButton onClick=handleClick>
        {renderIcon()}
      </MaterialUi.IconButton>
      <MaterialUi.Menu
        anchorEl={self.state.anchorElement}
        open_={Js.Option.isSome(self.state.anchorElement)}
        onClose={(_ev, _cause) => handleClose()}>
        {renderMenuItems(~onClick=handleClose, ())}
      </MaterialUi.Menu>
    </>;
  },
};
