open BsStorybook.Story;
open Styles;

let _module = [%bs.raw "module"];

module ScreenFrame = {
  let component = ReasonReact.statelessComponent("ScreenFrame");
  let make = children => {
    ...component,
    render: _self =>
      <div className={cn(["absolute", "absolute--fill", "flex"])}>
        ...children
      </div>,
  };
};

storiesOf("Screens", _module)
->(
    add("RegistrationCTA", () =>
      <ContextProvider.Client
        generateClassName={ReactJss.GenerateClassName.make()}>
        <RegistrationCTAScreen onSignIn={_ev => ()} onSignUp={_ev => ()} />
      </ContextProvider.Client>
    )
  )
->(
    add("SignUpScreen", () =>
      <ContextProvider.Client
        generateClassName={ReactJss.GenerateClassName.make()}>
        <ScreenFrame>
          <SignUpScreen
            renderSignUp={() => <div className={cn(["bg-brand"])} />}
          />
        </ScreenFrame>
      </ContextProvider.Client>
    )
  );
