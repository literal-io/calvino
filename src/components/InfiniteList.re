open Styles;

type state = {
  listRef: ref(option(Dom.element)),
  hasMoreData: ref(bool),
  isLoadingMoreData: bool,
};

type action =
  | HandleLoadMoreData
  | HandleLoadedMoreData;

let component = ReasonReact.reducerComponent("InfiniteList");

let handleListRef = (listRef, {ReasonReact.state}) =>
  state.listRef := Js.Nullable.toOption(listRef);

let handleScroll = (~onEndReached, ~endThreshold, elem) =>
  switch (elem) {
  | Some(elem) =>
    let scrollHeight = float_of_int(Webapi.Dom.Element.scrollHeight(elem));
    let clientHeight = float_of_int(Webapi.Dom.Element.clientHeight(elem));
    let scrollTop = Webapi.Dom.Element.scrollTop(elem);
    let threshold = endThreshold *. clientHeight;
    if (scrollHeight -. threshold < scrollTop +. clientHeight) {
      onEndReached();
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
      ~renderLoadingIndicator=?,
      _children,
    ) => {
  ...component,
  initialState: () => {
    listRef: ref(None),
    hasMoreData: ref(true),
    isLoadingMoreData: false,
  },
  didUpdate: ({newSelf}) => {
    let _ =
      handleScroll(
        ~onEndReached=
          newSelf.handle(((), self) => newSelf.send(HandleLoadMoreData)),
        ~endThreshold,
        newSelf.state.listRef^,
      );
    ();
  },
  reducer: (action, state) =>
    switch (action) {
    | HandleLoadMoreData =>
      state.hasMoreData^ && !state.isLoadingMoreData ?
        ReasonReact.UpdateWithSideEffects(
          {...state, isLoadingMoreData: true},
          self =>
            switch (Js.Nullable.toOption(onEndReached())) {
            | Some(promise) =>
              let _ =
                Js.Promise.then_(
                  () => {
                    self.send(HandleLoadedMoreData);
                    Js.Promise.resolve();
                  },
                  promise,
                );
              ();
            | None =>
              self.send(HandleLoadedMoreData);
              self.state.hasMoreData := false;
            },
        ) :
        ReasonReact.NoUpdate
    | HandleLoadedMoreData =>
      ReasonReact.Update({...state, isLoadingMoreData: false})
    },
  render: self => {
    let onScroll =
      Lodash.throttle(
        Utils.wrapBs(
          handleScroll(
            ~onEndReached=() => self.send(HandleLoadMoreData),
            ~endThreshold,
          ),
        ),
        200,
      );
    let items =
      data
      |> Js.Array.mapi((item, idx) =>
           <>
             {renderItem(item)}
             {idx < Js.Array.length(data) - 1 ?
                renderSeparator() : ReasonReact.null}
           </>
         );
    let loadingIndicator =
      switch (renderLoadingIndicator) {
      | Some(renderLoadingIndicator) =>
        renderLoadingIndicator(self.state.isLoadingMoreData)
      | _ => ReasonReact.null
      };
    switch (renderInnerContainer) {
    | Some(renderInnerContainer) =>
      <div
        ref={self.handle(handleListRef)}
        onScroll={_ev => onScroll(. self.state.listRef^)}
        className={cn([
          "overflow-y-scroll",
          "absolute",
          "absolute--fill",
          className->Cn.unpack,
        ])}>
        {renderInnerContainer(items)}
        loadingIndicator
      </div>
    | None =>
      <div
        ref={self.handle(handleListRef)}
        onScroll={_ev => onScroll(. self.state.listRef^)}
        className={cn([
          "overflow-y-scroll",
          "absolute",
          "absolute--fill",
          className->Cn.unpack,
        ])}>
        ...{Array.append(items, [|loadingIndicator|])}
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
