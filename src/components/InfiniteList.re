open Styles;

type state = {
  listRef: ref(option(Dom.element)),
  hasMoreData: ref(bool),
  isLoadingMoreData: ref(bool),
};

let component = ReasonReact.reducerComponent("InfiniteList");

let handleListRef = (listRef, {ReasonReact.state}) =>
  state.listRef := Js.Nullable.toOption(listRef);

let handleScroll = (~onEndReached, ~self, ~endThreshold, elem) =>
  switch (elem) {
  | Some(elem) =>
    let scrollHeight = float_of_int(Webapi.Dom.Element.scrollHeight(elem));
    let clientHeight = float_of_int(Webapi.Dom.Element.clientHeight(elem));
    let scrollTop = Webapi.Dom.Element.scrollTop(elem);
    let threshold = endThreshold *. clientHeight;
    if (scrollHeight -. threshold < scrollTop +. clientHeight) {
      self.ReasonReact.state.isLoadingMoreData := true;
      switch (Js.Nullable.toOption(onEndReached())) {
      | Some(promise) =>
        let _ =
          Js.Promise.then_(
            () => {
              self.handle(
                ((), {ReasonReact.state}) =>
                  state.isLoadingMoreData := false,
                (),
              );
              Js.Promise.resolve();
            },
            promise,
          );
        ();
      | None =>
        self.ReasonReact.state.isLoadingMoreData := false;
        self.ReasonReact.state.hasMoreData := false;
      };
    };
  | None => ()
  };

let make =
    (
      ~renderItem,
      ~data,
      ~renderSeparator,
      ~onEndReached,
      ~endThreshold,
      ~className=?,
      ~renderInnerContainer=?,
      _children,
    ) => {
  ...component,
  initialState: () => {
    listRef: ref(None),
    hasMoreData: ref(true),
    isLoadingMoreData: ref(false),
  },
  reducer: ((), _state) => ReasonReact.NoUpdate,
  render: self => {
    let onScroll =
      Lodash.throttle(
        Utils.wrapBs(handleScroll(~onEndReached, ~endThreshold, ~self)),
        200,
      );
    let items =
      data
      |> Js.Array.mapi((item, idx) =>
           <>
             {renderItem(item)}
             {
               idx < Js.Array.length(data) - 1 ?
                 renderSeparator() : ReasonReact.null
             }
           </>
         );
    switch (renderInnerContainer) {
    | Some(renderInnerContainer) =>
      <div
        ref={self.handle(handleListRef)}
        onScroll=(_ev => onScroll(. self.state.listRef^))
        className={
          cn([
            "overflow-y-scroll",
            "absolute",
            "absolute--fill",
            className->Cn.unpack,
          ])
        }>
        {renderInnerContainer(items)}
      </div>
    | None =>
      <div
        ref={self.handle(handleListRef)}
        onScroll=(_ev => onScroll(. self.state.listRef^))
        className={
          cn([
            "overflow-y-scroll",
            "absolute",
            "absolute--fill",
            className->Cn.unpack,
          ])
        }>
        ...items
      </div>
    };
  },
};

[@bs.deriving abstract]
type jsProps('a) = {
  renderItem: (. 'a) => ReasonReact.reactElement,
  data: Js.Array.t('a),
  renderSeparator: (. unit) => ReasonReact.reactElement,
  onEndReached: (. unit) => Js.Nullable.t(Js.Promise.t(unit)),
  className: Js.Nullable.t(string),
  endThreshold: float,
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~className=?jsProps->classNameGet |> Js.Nullable.toOption,
      ~renderItem=item => jsProps->renderItemGet(. item),
      ~onEndReached=() => jsProps->onEndReachedGet(.),
      ~endThreshold=jsProps->endThresholdGet,
      ~data=jsProps->dataGet,
      ~renderSeparator=() => jsProps->renderSeparatorGet(.),
      [||],
    )
  );
