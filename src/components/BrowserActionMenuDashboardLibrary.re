open Styles;

let component = ReasonReact.statelessComponent("BrowserActionMenuDashboardLibrary");

let make =
    (
      ~documents,
      ~onPaginateDocuments,
      ~readerPath,
      ~onDocumentTileClick,
      _children,
    ) => {
  ...component,
  render: _self =>
    <InfiniteList
      data=[|documents|]
      renderItem={data =>
        <DocumentTileMasonryGrid
          data
          readerPath
          columns=2
          gutter=36
          onDocumentTileClick
        />
      }
      renderLoadingIndicator={isLoadingMoreData =>
        <div
          className={cn([
            "flex",
            "flex-row",
            "justify-center",
            "items-center",
            "pv5",
            "bg-gray",
          ])}>
          <MaterialUi.CircularProgress
            variant=`Indeterminate
            size={`Int(48)}
            classes=[
              MaterialUi.CircularProgress.Classes.Root(
                cn(["bsl", "dn"->Cn.ifTrue(!isLoadingMoreData)]),
              ),
            ]
          />
        </div>
      }
      renderInnerContainer={children =>
        <div
          className={cn([
            "flex",
            "items-center",
            "flex-column",
            "bg-gray",
            "pt4",
          ])}>
          ...children
        </div>
      }
      renderSeparator={() => ReasonReact.null}
      endThreshold=2.0
      onEndReached=onPaginateDocuments
    />,
};

[@bs.deriving abstract]
type jsProps = {
  documents: Js.Array.t(Js.Json.t),
  onPaginateDocuments: (. unit) => Js.Nullable.t(Js.Promise.t(unit)),
  onDocumentTileClick: (. Js.Obj.t) => unit,
  readerPath: Js.String.t,
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~documents=
        jsProps
        |> documentsGet
        |> Js.Array.map(JavamonnBsLibrarian.DocumentModel.decode),
      ~onPaginateDocuments=Utils.applyBs(jsProps |> onPaginateDocumentsGet),
      ~readerPath=jsProps |> readerPathGet,
      [||],
    )
  );
