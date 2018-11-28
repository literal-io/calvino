open Styles;

type action =
  | SetIsReady(bool);

type state = {isReady: bool};

let component = ReasonReact.reducerComponent("DocumentTile");

let make =
    (~title, ~author, ~imageURL, ~onReady, _children) => {
  ...component,
  initialState: () => {isReady: false},
  reducer: (action, state) =>
    switch (action) {
    | SetIsReady(isReady) =>
      ReasonReact.UpdateWithSideEffects(
        {isReady: isReady},
        (_self => onReady()),
      )
    },
  render: self => {
    let elem =
      <div
        style={make(~width=px(200), ())}
        className={
          cn([
            "flex",
            "flex-column",
            "pointer",
            "vis-h"->Cn.ifTrue(!self.state.isReady),
            "absolute"->Cn.ifTrue(!self.state.isReady)
          ])
        }>
        <MaterialUi.Paper
          classes=[MaterialUi.Paper.Classes.Root("overflow-hidden")]>
          {
            switch (imageURL) {
            | Some(imageURL) =>
              <img
                src=imageURL
                onLoad=(_ev => self.send(SetIsReady(true)))
                onError=(_ev => self.send(SetIsReady(true)))
                className={cn(["w-100"])}
              />
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
      </div>;

    if (self.state.isReady) {
      elem;
    } else {
      /**
       * FIXME: data-packed should be passed down through a prop, not hardcoded. It's unclear
       * how to have Js.t with dynamic keys.
       */
      ReasonReact.cloneElement(elem, ~props={"data-packed": ""}, [||]);
    };
  },
};
