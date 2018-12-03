/**
 * Abstraction of InfiniteList for rendering several heterogenous sections
 * with headers.
 */

let component = ReasonReact.statelessComponent("SectionList");

module TitledSection {
  [@bs.deriving abstract]
  type t('a) = {
    title: string,
    data: array('a),
  };

  let make = t;
};

let make =
    (
      ~data,
      ~renderSectionHeader,
      ~renderItem,
      ~renderSeparator,
      ~renderInnerContainer=?,
      ~onEndReached,
      ~endThreshold,
      ~className=?,
      _children,
    ) => {
  ...component,
  render: _self =>
    <InfiniteList
      ?className
      renderItem={
        item => <> {renderSectionHeader(item)} {renderItem(item)} </>
      }
      ?renderInnerContainer
      renderSeparator
      onEndReached
      endThreshold
      data
    />,
};

[@bs.deriving abstract]
type jsProps('a) = {
  renderItem: (. 'a) => ReasonReact.reactElement,
  renderInnerContainer:
    Js.Nullable.t(
      (. array(ReasonReact.reactElement)) => ReasonReact.reactElement,
    ),
  data: Js.Array.t('a),
  renderSectionHeader: (. 'a) => ReasonReact.reactElement,
  renderSeparator: (. unit) => ReasonReact.reactElement,
  onEndReached: (. unit) => Js.Nullable.t(Js.Promise.t(unit)),
  className: Js.Nullable.t(string),
  endThreshold: float,
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~className=?jsProps->classNameGet->Js.Nullable.toOption,
      ~renderItem=item => jsProps->renderItemGet(. item),
      ~renderSectionHeader=item => jsProps->renderSectionHeaderGet(. item),
      ~renderSeparator=() => jsProps->renderSeparatorGet(.),
      ~renderInnerContainer=?
        jsProps->renderInnerContainerGet->Js.Nullable.toOption
        |> Js.Option.map((. renderInnerContainer) => {
             let fn = children => renderInnerContainer(. children);
             fn;
           }),
      ~endThreshold=jsProps->endThresholdGet,
      ~onEndReached=() => jsProps->onEndReachedGet(.),
      ~data=jsProps->dataGet,
      [||],
    )
  );
