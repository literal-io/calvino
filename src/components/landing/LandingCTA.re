open Styles;

type state = {installText: option(string)};

type action =
  | SetInstallText;

let component = ReasonReact.reducerComponent("LandingCTA");

let make = _children => {
  ...component,
  initialState: () => {installText: None},
  didMount: self => self.send(SetInstallText),
  reducer: (action, _state) =>
    switch (action) {
    | SetInstallText =>
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
      ReasonReact.Update({
        installText:
          Some(
            browser === "Firefox" ?
              "Install Firefox Add-On" : "Install Chrome Extension",
          ),
      });
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
        <div className={cn(["pl", "f2-r", "b"])}>
          {ReasonReact.string("The PDF Reader of the Web.")}
        </div>
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
            style={make(~minWidth=px(240), ())}
            classes=[
              MaterialUi.Button.Classes.Root(cn(["bg-accent-100-o60"])),
              MaterialUi.Button.Classes.Label(cn(["white"])),
            ]
            variant=`Raised>
            {self.state.installText |> Js.Option.getWithDefault("")}
          </MaterialUi.Button>
          <Spacer size=3 />
          <MaterialUi.Button
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
