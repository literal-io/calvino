open Styles;

let component = ReasonReact.reducerComponent("DocumentActivity");

let make =
    (
      ~earliestDocumentOpenActivity,
      ~latestDocumentOpenActivity,
      ~document,
      _children,
    ) => {
  ...component,
  render: self => <div />,
};
