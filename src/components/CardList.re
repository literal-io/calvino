open Styles;

type state = {
  handleScroll: (. option(Dom.element)) => unit,
  listRef: ref(option(Dom.element)),
};

let component = ReasonReact.reducerComponent("CardList");

let handleListRef = (listRef, {ReasonReact.state}) =>
  state.listRef := Js.Nullable.toOption(listRef);

let make =
    (
      ~renderCard,
      ~data,
      ~renderSeparator,
      ~onEndReached,
      ~endThreshold,
      _children,
    ) => {
  ...component,
  initialState: () => {
    listRef: ref(None),
    handleScroll:
      Lodash.debounce(
        (. elem) =>
          switch (elem) {
          | Some(elem) =>
            let scrolledRatio =
              Webapi.Dom.Element.(
                scrollTop(elem) /. float_of_int(scrollHeight(elem))
              );
            if (scrolledRatio > endThreshold) {
              onEndReached();
            };
          | None => ()
          },
        200,
      ),
  },
  reducer: ((), _state) => ReasonReact.NoUpdate,
  render: self =>
    <div
      ref={self.handle(handleListRef)}
      onScroll={_ev => self.state.handleScroll(. self.state.listRef^)}
      className={cn(["overflow-y-scroll", "flex-column", "h-100"])}>
      ...{
           data
           |> Js.Array.mapi((card, idx) =>
                <>
                  {renderCard(card)}
                  {
                    idx < Js.Array.length(data) - 1 ?
                      renderSeparator() : ReasonReact.null
                  }
                </>
              )
         }
    </div>,
};

[@bs.deriving abstract]
type jsProps('a) = {
  renderCard: 'a => ReasonReact.reactElement,
  data: Js.Array.t('a),
  renderSeparator: unit => ReasonReact.reactElement,
  onEndReached: unit => unit,
  endThreshold: float
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~renderCard=jsProps->renderCardGet,
      ~onEndReached=jsProps->onEndReachedGet,
      ~endThreshold=jsProps->endThresholdGet,
      ~data=jsProps->dataGet,
      ~renderSeparator=jsProps->renderSeparatorGet,
      [||],
    )
  );
