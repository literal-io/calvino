open Styles;
let component = ReasonReact.statelessComponent("LandingNavigationBar");

let renderButton = (~label, ~href, ()) =>
  <MaterialUi.Button
    href
    style={make(~padding="14px 16px", ())}
    variant=`Flat
    classes=[Label(cn(["sl"]))]>
    label
  </MaterialUi.Button>;

let renderAnalyticsButton = (~label, ~href, ~eventType, ~eventOptions, ()) =>
  <AnalyticsButton
    href
    style={make(~padding="14px 16px", ())}
    variant=`Flat
    classes=[Label(cn(["sl"]))]
    eventType
    eventOptions>
    label
  </AnalyticsButton>;

let make = (~browser, _children) => {
  let installURL =
    switch (browser) {
    | `Firefox => Constants.firefoxExtensionURL
    | _ => Constants.chromeExtensionURL
    };
  {
    ...component,
    render: _self =>
      <div className={cn(["flex", "flex-row", "items-center", "mh5", "mv3"])}>
        <div className={cn(["pl", "b", "f4"])}>
          {ReasonReact.string("Literal.")}
        </div>
        <Spacer size=4 />
        {
          renderAnalyticsButton(
            ~label="Install",
            ~href=installURL,
            ~eventType=`Event,
            ~eventOptions=
              GAnalytics.eventOptions(
                ~ec="extension",
                ~ea="clicked-install-prompt",
                (),
              ),
            (),
          )
        }
        <Spacer size=2 />
        {renderButton(~label="Sign Up", ~href="/sign-up", ())}
        <Spacer size=2 />
        {renderButton(~label="Sign In", ~href="/sign-in", ())}
        <Spacer size=2 />
        {renderButton(~label="Pricing", ~href="/pricing", ())}
        <Spacer size=2 />
        {renderButton(~label="FAQ", ~href="/faq", ())}
      </div>,
  };
};
