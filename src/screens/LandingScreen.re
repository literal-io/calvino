open Styles;
let component = ReasonReact.statelessComponent("LandingScreen");

let make = (~readerURL, ~userAgent, _children) => {
  ...component,
  render: _self => {
    let browser =
      userAgent
      |> Bowser.make
      |> Bowser.getBrowser
      |> Bowser.getBrowserName
      |> Js.Option.getWithDefault(`Chrome);
    <div
      className={cn([
        "ff-r",
        "bg-brand",
        "flex",
        "flex-auto",
        "overflow-auto",
        "flex-column",
      ])}>
      <LandingNavigationBar browser />
      <div
        className={cn([
          "mh5",
          "flex",
          "flex-row",
          "flex-shrink-0",
          "ph5",
          "vh-100",
          "justify-center",
        ])}>
        <div className={cn(["d-maxw", "flex-auto", "flex"])}>
          <LandingCTA browser />
          <LandingReaderTile readerURL />
        </div>
      </div>
      <LandingLibrarySection />
      <Spacer size=4 />
      <LandingFeaturesSection />
      <Spacer size=4 />
      <LandingFooterSection browser />
    </div>;
  },
};

[@bs.deriving abstract]
type jsProps = {
  readerURL: Js.String.t,
  userAgent: Js.String.t,
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~readerURL=jsProps |> readerURLGet,
      ~userAgent=jsProps |> userAgentGet,
      [||],
    )
  );
