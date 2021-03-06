open Styles;

let component = ReasonReact.statelessComponent("LandingFooterSection");
let make = (~browser, _children) => {
  let (installLabel, installText, installUrl) =
    switch (browser) {
    | `Firefox => (
        "Install Firefox Add-On",
        "Install Literal for Firefox to get started.",
        Constants.firefoxExtensionURL,
      )
    | _ => (
        "Install Chrome Extension",
        "Install Literal for Chrome to get started.",
        Constants.chromeExtensionURL,
      )
    };
  {
    ...component,
    render: _self =>
      <div
        className={
          cn(["flex", "flex-row", "justify-center", "items-center", "pb6"])
        }>
        <div style={make(~minWidth=px(1000), ())}>
          <MaterialUi.Paper
            classes=[Root(cn(["bg-accent-100-o60", "br1"]))]>
            <div
              className={cn(["flex", "flex-row", "pa5", "justify-between"])}>
              <div className={cn(["flex", "flex-column"])}>
                <LandingHeaderText className={cn(["b", "pl"])}>
                  "Enhance Your Reading Experience."
                </LandingHeaderText>
                <Spacer size=2 />
                <div className={cn(["pl", "f4"])}>
                  {ReasonReact.string(installText)}
                </div>
              </div>
              <div className={cn(["flex", "justify-center", "items-center"])}>
                <AnalyticsButton
                  style={make(~padding="14px 42px", ())}
                  href=installUrl
                  classes=[Root(cn(["bg-brand"])), Label(cn(["white"]))]
                  eventType=`Event
                  eventOptions={
                    GAnalytics.eventOptions(
                      ~ec="extension",
                      ~ea="clicked-install-prompt",
                      (),
                    )
                  }
                  variant=`Raised>
                  installLabel
                </AnalyticsButton>
              </div>
            </div>
          </MaterialUi.Paper>
        </div>
      </div>,
  };
};
