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
  )
->(
    add("DashboardScreen", () =>
      <ContextProvider.Client
        generateClassName={ReactJss.GenerateClassName.make()}>
        <ScreenFrame>
          <DashboardScreen
            documents={Array.init(20, _idx => Mocks.document())}
            highlights={
              Array.init(20, _idx =>
                JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.make(
                  ~source=Mocks.documentAnnotation(),
                  ~target=Mocks.document(),
                  (),
                )
              )
            }
            readerPath="http://localhost:9001"
            userProfileId={BsFaker.Random.uuid()}
            onPaginateHighlights={() => Js.Nullable.null}
            onPaginateDocuments={() => Js.Nullable.null}
            onShareClicked={_highlight => ()}
            onAddDocumentClicked={_sourceType => ()}
          />
        </ScreenFrame>
      </ContextProvider.Client>
    )
  );
