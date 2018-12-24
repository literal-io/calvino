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
            recentDocument={Some(Mocks.document())}
            recentActivity={
              Some(
                ProfileSection.ActivityModel.make(
                  ~documentsCreated=Js.Math.random_int(8, 40),
                  ~highlightsCreated=Js.Math.random_int(8, 4),
                  ~pagesRead=Js.Math.random_int(20, 120),
                ),
              )
            }
            readerPath="http://localhost:9001"
            userProfileId={BsFaker.Random.uuid()}
            onPaginateHighlights={() => Js.Nullable.null}
            onPaginateDocuments={() => Js.Nullable.null}
            onAddDocumentClicked={_sourceType => ()}
          />
        </ScreenFrame>
      </ContextProvider.Client>
    )
  )
->(
    add("LandingScreen", () =>
      <ContextProvider.Client
        generateClassName={ReactJss.GenerateClassName.make()}>
        <ScreenFrame>
          <LandingScreen
            readerURL="https://literal.io/static/borges/index.html#/?type=web&url=https%3A%2F%2Fstorage.googleapis.com%2Fliteral-static%2Fthe-library-of-babel-by-jorge-luis-borges.pdf"
            userAgent={
              Webapi.Dom.(window |> Window.navigator)
              |> Bowser.asNavigator
              |> Bowser.userAgentGet
            }
          />
        </ScreenFrame>
      </ContextProvider.Client>
    )
  );
