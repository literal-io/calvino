open BsStorybook.Story;
open Styles;

let _module = [%bs.raw "module"];

storiesOf("Extension Browser Action Menu", _module)
->(
    add("BrowserActionMenuDashboardLibrary", () =>
      <ContextProvider.Client
        generateClassName={ReactJss.GenerateClassName.make()}>
        <div
          className={cn([
            "ep-h",
            "ep-w",
            "ov-h",
            "ff-r",
            "flex",
            "items-center",
          ])}>
          <BrowserActionMenuDashboardLibrary
            documents={Array.init(20, _idx => Mocks.document())}
            readerPath="http://localhost:9001"
            onPaginateDocuments={() =>
              Js.Promise.make((~resolve as _resolve, ~reject as _reject) =>
                ()
              )
              |> Js.Nullable.return
            }
            onDocumentTileClick={(url) => { 
              Js.log2("onDocumentTileClick", url);
            }}
          />
        </div>
      </ContextProvider.Client>
    )
)
