open Styles;
let component = ReasonReact.statelessComponent("LandingScreen");

let make = (~readerURL, _children) => {
  ...component,
  render: _self =>
    <div
      className={
        cn([
          "ff-r",
          "bg-brand",
          "flex",
          "flex-auto",
          "overflow-auto",
          "flex-column",
        ])
      }>
      <div
        className={
          cn(["mh5", "flex", "flex-row", "flex-shrink-0", "pa5", "vh-100"])
        }>
        <LandingCTA />
        <LandingReaderTile readerURL />
      </div>
      <LandingLibrarySection />
      <LandingFeaturesSection />
    </div>,
};

[@bs.deriving abstract]
type jsProps = {readerURL: Js.String.t};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(~readerURL=jsProps |> readerURLGet, [||])
  );
