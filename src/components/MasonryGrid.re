/**
 * A grid layout meant to be rendered as a child of a list component.
 */

type state = {
  containerRef: ref(option(Dom.element)),
  bricks: ref(option(Bricks.t)),
};

let component = ReasonReact.reducerComponent("MasonryGrid");

let handleContainerRef =
    (~columns, ~gutter, containerRef, {ReasonReact.state}) =>
  switch (state.containerRef^, Js.Nullable.toOption(containerRef)) {
  | (None, Some(containerRef)) =>
    state.containerRef := Some(containerRef);
    let bricks =
      Bricks.(
        Params.make(
          ~container=containerRef,
          ~packed="packed",
          ~sizes=[|Params.makeSize(~columns, ~gutter, ())|],
        )
        |> make
      );
    let _ = Bricks.pack(bricks);
    state.bricks := Some(bricks);
    ();
  | _ => () /* Bricks initialized, noop */
  };

let make = (~data, ~renderItem, ~columns, ~gutter, _children) => {
  ...component,
  initialState: () => {containerRef: ref(None), bricks: ref(None)},
  reducer: ((), state) => ReasonReact.NoUpdate,
  didUpdate: ({oldSelf, newSelf}) => {
    newSelf.state.bricks^ |> Js.Option.map(Utils.wrapBs(Bricks.update));
    ();
  },
  render: self =>
    <div ref={self.handle(handleContainerRef(~columns, ~gutter))}>
      ...{Array.map(item => renderItem(item), data)}
    </div>,
};
