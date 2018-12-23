open Styles;

type state = {
  installText: option(string),
  installUrl: option(string),
};

type action =
  | SetInstallData;

let component = ReasonReact.reducerComponent("LandingCTA");

let make = _children => {
  ...component,
  initialState: () => {installText: None, installUrl: None},
  didMount: self => self.send(SetInstallData),
  reducer: (action, _state) =>
    switch (action) {
    | SetInstallData =>
      let browser =
        Bowser.(
          Webapi.Dom.window
          |> Webapi.Dom.Window.navigator
          |> asNavigator
          |> userAgentGet
          |> make
          |> getBrowser
          |> nameGet
        );
      ReasonReact.Update(
        browser === "Firefox" ?
          {
            installText: Some("Install Firefox Add-On"),
            installUrl:
              Some(
                "https://addons.mozilla.org/en-US/firefox/addon/literal-pdf-reader/",
              ),
          } :
          {
            installText: Some("Install Chrome Extension"),
            installUrl:
              Some(
                "https://chrome.google.com/webstore/detail/aobcehhaeapnlhliodjobodhgmemimnl",
              ),
          },
      );
    },
  render: self =>
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
            style={make(~minWidth=px(240), ~padding="12px 16px", ())}
            href={self.state.installUrl |> Js.Option.getWithDefault("")}
            classes=[
              MaterialUi.Button.Classes.Root(cn(["bg-accent-100-o60"])),
              MaterialUi.Button.Classes.Label(cn(["white"])),
            ]
            variant=`Raised>
            {self.state.installText |> Js.Option.getWithDefault("")}
          </MaterialUi.Button>
          <Spacer size=3 />
          <MaterialUi.Button
            style={make(~padding="12px 16px", ())}
            href="/faq"
            classes=[
              MaterialUi.Button.Classes.Root(cn(["b-accent-100-o60"])),
              MaterialUi.Button.Classes.Label(cn(["accent-100-o60"])),
            ]
            variant=`Outlined>
            {ReasonReact.string("Learn More")}
          </MaterialUi.Button>
        </div>
      </div>
    </div>,
};
