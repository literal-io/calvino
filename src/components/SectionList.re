/**
 * Abstraction of InfiniteList for rendering several heterogenous sections
 * with headers.
 */

let component = ReasonReact.statelessComponent("SectionList");

let make =
    (
      ~data,
      ~renderSectionHeader,
      ~renderItem,
      ~renderSectionSeparator,
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
      renderSeparator=renderSectionSeparator
      onEndReached
      endThreshold
      data
    />,
};
