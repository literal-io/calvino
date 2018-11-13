open Styles;
let component = ReasonReact.statelessComponent("RegistrationCTAScreenRe");

type featureSection = {
  icon: ReasonReact.reactElement,
  title: string,
  description: string,
};

let make = (~onSignIn, ~onSignUp, _children) => {
  ...component,
  render: _self =>
    <div className={cn(["ep-h", "ep-w", "ff-r", "bg-brand"])}>
      <div className={cn(["pa3_5", "flex", "flex-column"])}>
        <span className={cn(["b", "f3", "pl"])}>
          {ReasonReact.string("Literal")}
        </span>
        <span className={cn(["f4", "pl"])}>
          {ReasonReact.string("PDF Reader is active.")}
        </span>
      </div>
      <div className={cn(["bg-accent-100-o60", "pa3_5"])}>
        <span className={cn(["f4", "pl"])}>
          {
            ReasonReact.string("Create a free account to access all features.")
          }
        </span>
      </div>
      <RegistrationIconList
        className={cn(["pa3_5", "pv3"])}
        iconStyle={pl +++ square(36)}
        iconClassName={cn(["pl", "sq36"])}
        titleClassName={cn(["f7", "pl", "b", "mb1"])}
        descriptionClassName={cn(["f7", "sl"])}
        renderSeparator={() => <div className={cn(["mb3"])} />}
      />
      <div
        className={
          cn([
            "pa3_5",
            "pt0",
            "flex",
            "flex-column",
            "justify-center",
            "items-center",
          ])
        }>
        MaterialUi.(
          <Button
            onClick=onSignUp
            variant=`Contained
            fullWidth=true
            classes=[Root(cn(["bg-accent-100-o60-i", "h42-i"]))]>
            <span className={cn(["pl", "b"])}>
              {ReasonReact.string("Create Account")}
            </span>
          </Button>
        )
        <div className={cn(["mb2"])} />
        MaterialUi.(
          <Button onClick=onSignIn variant=`Text>
            <div
              className={
                cn(["flex", "flex-column", "justify-center", "items-center"])
              }>
              <span className={cn(["pl", "f7", "ttn"])}>
                {ReasonReact.string("Already have an account?")}
              </span>
              <span className={cn(["pl", "f7", "ttn"])}>
                {ReasonReact.string("Sign In")}
              </span>
            </div>
          </Button>
        )
      </div>
    </div>,
};
[@bs.deriving abstract]
type jsProps = {
  onSignIn: ReactEvent.Mouse.t => unit,
  onSignUp: ReactEvent.Mouse.t => unit,
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(~onSignIn=jsProps->onSignInGet, ~onSignUp=jsProps->onSignUpGet, [||])
  );
