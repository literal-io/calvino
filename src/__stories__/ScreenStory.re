open BsStorybook.Story;

let _module = [%bs.raw "module"];

storiesOf("Screens", _module)
->(
    add("RegistrationCTA", () =>
      <RegistrationCTAScreen onSignIn={_ev => ()} onSignUp={_ev => ()} />
    )
  );
