module type RawReactClass = {let reactClass: ReasonReact.reactClass;};

module MakeIcon = (RawReactClass: RawReactClass) => {
  let make = (~style=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=RawReactClass.reactClass,
      ~props={"style": Js.Nullable.fromOption(style)},
      children,
    );
};

module CloudOutline =
  MakeIcon({
    [@bs.module "@material-ui/icons/CloudOutlined"]
    external reactClass: ReasonReact.reactClass = "default";
  });

module Highlight =
  MakeIcon({
    [@bs.module "@material-ui/icons/Highlight"]
      external reactClass: ReasonReact.reactClass = "default";
  })

module LibraryBooks =
  MakeIcon({
    [@bs.module "@material-ui/icons/LibraryBooks"]
      external reactClass: ReasonReact.reactClass = "default";
  })

module TextFields =
  MakeIcon({
    [@bs.module "@material-ui/icons/TextFields"]
      external reactClass: ReasonReact.reactClass = "default";
  })

module Share =
  MakeIcon({
    [@bs.module "@material-ui/icons/Share"]
      external reactClass: ReasonReact.reactClass = "default";
  })

module Add =
  MakeIcon({
    [@bs.module "@material-ui/icons/Add"]
      external reactClass: ReasonReact.reactClass = "default";
  })
