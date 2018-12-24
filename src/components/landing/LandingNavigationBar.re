open Styles;
let component = ReasonReact.statelessComponent("LandingNavigationBar");

let renderButton = (~label, ~href, ()) =>
  <MaterialUi.Button
    href
    style={make(~padding="18px 16px", ())}
    variant=`Flat
    classes=[Label(cn(["sl"]))]>
    label
  </MaterialUi.Button>;

let make = (~browser, _children) => {
  let installURL =
    switch (browser) {
    | `Firefox => "https://addons.mozilla.org/en-US/firefox/addon/literal-pdf-reader/"
    | _ => "https://chrome.google.com/webstore/detail/aobcehhaeapnlhliodjobodhgmemimnl"
    };
  {
    ...component,
    render: _self =>
      <div className={cn(["flex", "flex-row", "items-center", "mh5", "mv3"])}>
        <div className={cn(["pl", "b", "f4"])}>
          {ReasonReact.string("Literal.")}
        </div>
        <Spacer size=4 />
        {renderButton(~label="Install", ~href=installURL, ())}
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
