open Styles;
let component = ReasonReact.statelessComponent("LandingLibrarySection");

let make = _children => {
  ...component,
  render: _self =>
    <div
      style={
        make(~marginTop=vh(-20), ~paddingTop=vh(10), ~paddingBottom=vh(10), ())
      }
      className={
        cn([
          "flex",
          "flex-row",
          "bg-accent-100-o72",
          "flex-shrink-0",
          "ph5",
        ])
      }>
      <div
        style={make(~maxWidth=px(500), ())}
        className={cn(["flex", "flex-column", "mh5"])}>
        <LandingHeaderText className={cn(["brand-sl", "b"])}>
          "Your Digital Librarian."
        </LandingHeaderText>
        <Spacer size=3 />
        <div className={cn(["brand-sl", "f4"])}>
          {
            ReasonReact.string(
              "Literal is much more than just a reader - a powerful document management system organizes, archives, and enhances your document library.",
            )
          }
        </div>
        <Spacer size=3 />
        <div className={cn(["brand-sl", "f4"])}>
          {
            ReasonReact.string(
              "Highlight, search, and share documents from your library.",
            )
          }
        </div>
      </div>
    </div>,
};
