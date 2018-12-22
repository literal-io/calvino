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
        className={cn(["mh5", "flex", "flex-row", "flex-shrink-0", "pa5", "vh-100"])}>
        <LandingCTA />
        <LandingReaderSection readerURL />
      </div>
      <div
        style={make(~top=vh(-20), ())}
        className={
          cn([
            "flex",
            "flex-row",
            "vh-75",
            "bg-accent-100-o72",
            "flex-shrink-0",
            "relative",
          ])
        }
      />
    </div>,
};
