open Styles;
let component = ReasonReact.statelessComponent("LandingScreen");

let renderTextSection = () =>
  <div className={cn(["flex", "flex-column", "flex-1"])}>
    <div
      style={make(~maxWidth=px(500), ~paddingTop="17%", ())}
      className={cn(["flex", "flex-column"])}>
      <div className={cn(["pl", "f4"])}>
        {ReasonReact.string("Literal.")}
      </div>
      <div className={cn(["mv1"])} />
      <div className={cn(["pl", "f2-r", "b"])}>
        {ReasonReact.string("The PDF Reader of the Web.")}
      </div>
      <div className={cn(["mv3"])} />
      <div className={cn(["pl", "f4"])}>
        {
          ReasonReact.string(
            "Literal makes PDF documents discoverable, searchable, and shareable, by integrating deeply with your Web browser.",
          )
        }
      </div>
      <div className={cn(["mv3"])} />
      <div className={cn(["pl", "f4"])}>
        {
          ReasonReact.string(
            "Literal is the best way to read and interact with PDF documents online.",
          )
        }
      </div>
    </div>
  </div>;

let renderReaderSection = (~readerURL, ()) =>
  <div className={cn(["justify-center", "flex-1", "flex-column", "flex"])}>
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
  </div>;

let make = (~readerURL, _children) => {
  ...component,
  render: _self =>
    <div className={cn(["flex-auto", "ff-r", "bg-brand", "pa5", "flex"])}>
      <div className={cn(["mh5", "flex", "flex-row", "flex-auto"])}>
        {renderTextSection()}
        {renderReaderSection(~readerURL, ())}
      </div>
    </div>,
};
