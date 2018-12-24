open Styles;

let component = ReasonReact.statelessComponent("LandingCTA");

let make = (~browser, _children) => {
  ...component,
  render: _self => {
    let (installText, installUrl) =
      switch (browser) {
      | `Firefox => (
          "Install Firefox Add-On",
          "https://addons.mozilla.org/en-US/firefox/addon/literal-pdf-reader/",
        )
      | _ => (
          "Install Chrome Extension",
          "https://chrome.google.com/webstore/detail/aobcehhaeapnlhliodjobodhgmemimnl",
        )
      };
    <div className={cn(["flex", "flex-column", "flex-1"])}>
      <div
        style={make(~maxWidth=px(500), ~paddingTop="20%", ())}
        className={cn(["flex", "flex-column"])}>
        <div className={cn(["pl", "f4"])}>
          {ReasonReact.string("Literal.")}
        </div>
        <Spacer size=1 />
        <LandingHeaderText className={cn(["pl", "b"])}>
          "The PDF Reader of the Web."
        </LandingHeaderText>
        <Spacer size=3 />
        <div className={cn(["pl", "f4"])}>
          {
            ReasonReact.string(
              "Literal is the best way to read and interact with online PDF documents.",
            )
          }
        </div>
        <Spacer size=3 />
        <div className={cn(["pl", "f4"])}>
          {
            ReasonReact.string(
              "Literal makes PDF documents discoverable, searchable, and shareable by integrating deeply with your Web browser.",
            )
          }
        </div>
        <Spacer size=3 />
        <div className={cn(["flex-row", "flex"])}>
          <MaterialUi.Button
            style={make(~minWidth=px(240), ~padding="18px 16px", ())}
            href=installUrl
            classes=[
              MaterialUi.Button.Classes.Root(cn(["bg-accent-100-o60"])),
              MaterialUi.Button.Classes.Label(cn(["white"])),
            ]
            variant=`Raised>
            installText
          </MaterialUi.Button>
          <Spacer size=3 />
          <MaterialUi.Button
            style={make(~padding="18px 16px", ())}
            href="/faq"
            classes=[
              MaterialUi.Button.Classes.Root(cn(["b-pl"])),
              MaterialUi.Button.Classes.Label(cn(["pl"])),
            ]
            variant=`Outlined>
            {ReasonReact.string("Learn More")}
          </MaterialUi.Button>
        </div>
      </div>
    </div>;
  },
};
