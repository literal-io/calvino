open Styles;
let component = ReasonReact.statelessComponent("LandingLibrarySection");

let make = _children => {
  ...component,
  render: _self =>
    <div
      style={
        make(
          ~marginTop=vh(-30),
          ~paddingTop=vh(10),
          ~paddingBottom=vh(10),
          (),
        )
      }
      className={
        cn(["flex", "flex-row", "bg-accent-100-o72", "flex-shrink-0", "ph6"])
      }>
      <div
        style={make(~maxWidth=px(600), ())}
        className={cn(["flex", "flex-column", "flex-1", "ml6", "mr5"])}>
        <LandingHeaderText className={cn(["bpl", "b", "tr"])}>
          "Your Digital Librarian."
        </LandingHeaderText>
        <Spacer size=3 />
        <div className={cn(["bpl", "f4", "tr"])}>
          {
            ReasonReact.string(
              "Literal is much more than just a reader - a powerful document management system organizes, archives, and enhances your document library.",
            )
          }
        </div>
        <Spacer size=3 />
        <div className={cn(["bpl", "f4", "tr"])}>
          {
            ReasonReact.string(
              "Highlight, search, and share documents from your library.",
            )
          }
        </div>
      </div>
      <Spacer size=6 />
      <div className={cn(["flex-1", "mr6", "flex-shrink-0"])} />
    </div>,
};
