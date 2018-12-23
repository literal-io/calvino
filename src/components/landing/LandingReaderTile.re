open Styles;
let component = ReasonReact.statelessComponent("LandingReaderTile");

let make = (~readerURL, _children) => {
  ...component,
  render: _self =>
    <div
      className={
        cn(["justify-center", "flex-1", "flex-column", "flex", "z-1"])
      }>
      <MaterialUi.Paper
        classes=[
          MaterialUi.Paper.Classes.Root(
            cn(["flex-1", "overflow-hidden", "relative", "flex"]),
          ),
        ]>
        <iframe
          src=readerURL
          className={
            cn(["absolute", "absolute--fill", "w-100", "h-100", "bn", "br-1"])
          }
        />
      </MaterialUi.Paper>
    </div>,
};
