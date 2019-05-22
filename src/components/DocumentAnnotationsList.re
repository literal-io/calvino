open Styles;

let component = ReasonReact.statelessComponent("DocumentAnnotationsList");

let make =
    (
      ~documentAnnotations,
      ~onPaginateDocumentAnnotations,
      ~onDocumentAnnotationTileClick,
      ~onDocumentAnnotationTileShare,
      ~userProfileId,
      ~readerPath,
      ~hideDocumentInfo=?,
      _children,
    ) => {
  ...component,
  render: _self => {
    <InfiniteList
      data=documentAnnotations
      renderItem={documentAnnotation =>
        <DocumentAnnotationTile
          onClick=onDocumentAnnotationTileClick
          onShareClicked={() => {
            let _ =
              Utils.shareDocumentAnnotation(
                ~userProfileId,
                documentAnnotation,
              );
            let _ = onDocumentAnnotationTileShare();
            ();
          }}
          ?hideDocumentInfo
          title=JavamonnBsLibrarian.(
            documentAnnotation
            |> JoinedModel.DocumentAnnotationToDocument.target
            |> DocumentModel.title
          )
          author=JavamonnBsLibrarian.(
            documentAnnotation
            |> JoinedModel.DocumentAnnotationToDocument.target
            |> DocumentModel.author
          )
          text=JavamonnBsLibrarian.(
            documentAnnotation
            |> JoinedModel.DocumentAnnotationToDocument.source
            |> DocumentAnnotationModel.text
            |> Js.Option.getWithDefault("")
          )
          annotationURL={Utils.makeDocumentAnnotationURL(
            ~readerPath,
            ~document=
              JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.target(
                documentAnnotation,
              ),
            JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.source(
              documentAnnotation,
            ),
          )}
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
      renderSeparator={() => <div className={cn(["mv3"])} />}
      endThreshold=2.0
      renderInnerContainer={children =>
        <div
          className={cn([
            "flex",
            "items-stretch",
            "flex-column",
            "bg-gray",
            "pt4",
            "ph3",
          ])}>
          ...children
        </div>
      }
      onEndReached=onPaginateDocumentAnnotations
    />;
  },
};

[@bs.deriving abstract]
type jsProps = {
  documentAnnotations: Js.Array.t(Js.Json.t),
  readerPath: string,
  userProfileId: string,
  onPaginateDocumentAnnotations:
    (. unit) => Js.Nullable.t(Js.Promise.t(unit)),
  onDocumentAnnotationTileShare: (. unit) => unit,
  onDocumentAnnotationTileClick: (. string) => unit,
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~documentAnnotations=
        jsProps
        |> documentAnnotationsGet
        |> Js.Array.map(
             JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.decodeExn,
           )
        |> Js.Array.filter(Js.Option.isSome)
        |> Js.Array.map(Js.Option.getExn),
      ~onPaginateDocumentAnnotations=
        Utils.applyBs(jsProps |> onPaginateDocumentAnnotationsGet),
      ~onDocumentAnnotationTileShare=
        Utils.applyBs(jsProps |> onDocumentAnnotationTileShare),
      ~onDocumentAnnotationTileClick=
        Utils.applyBs1(jsProps |> onDocumentAnnotationTileClick),
      ~readerPath=jsProps |> readerPathGet,
      ~userProfileId=jsProps |> userProfileIdGet,
      [||],
    )
  );
