open Styles;
let component = ReasonReact.statelessComponent("DashboardScreen");

let make =
    (
      ~documents,
      ~highlights,
      ~onPaginateDocuments,
      ~onPaginateHighlights,
      ~onShareClicked,
      ~onAddDocumentClicked,
      ~readerPath,
      ~userProfileId,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div className={cn(["flex", "flex-row", "flex-auto", "ff-r"])}>
      <div className={cn(["relative", "flex-2"])}>
        <LibrarySection
          documents
          onPaginateDocuments
          onAddDocumentClicked
          readerPath
        />
      </div>
      <div className={cn(["relative", "flex-1"])}>
        <HighlightsSection
          highlights
          onPaginateHighlights
          onShareClicked
          readerPath
          userProfileId
        />
      </div>
    </div>,
};

[@bs.deriving abstract]
type jsProps = {
  documents: Js.Array.t(Js.Json.t),
  highlights: Js.Array.t(Js.Json.t),
  readerPath: Js.String.t,
  userProfileId: Js.String.t,
  onPaginateDocuments: (. unit) => Js.Nullable.t(Js.Promise.t(unit)),
  onPaginateHighlights: (. unit) => Js.Nullable.t(Js.Promise.t(unit)),
  onShareClicked: (. Js.Json.t) => unit,
  onAddDocumentClicked: (. string) => unit,
};

let default =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~documents=
        jsProps
        |> documentsGet
        |> Js.Array.map(JavamonnBsLibrarian.DocumentModel.decode),
      ~highlights=
        jsProps
        |> highlightsGet
        |> Js.Array.map(
             JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.decode,
           )
        |> Js.Array.filter(Js.Option.isSome)
        |> Js.Array.map(Js.Option.getExn),
      ~readerPath=jsProps |> readerPathGet,
      ~userProfileId=jsProps |> userProfileIdGet,
      ~onPaginateDocuments=Utils.applyBs(jsProps |> onPaginateDocumentsGet),
      ~onPaginateHighlights=Utils.applyBs(jsProps |> onPaginateHighlightsGet),
      ~onShareClicked=
        joinedDocumentAnnotation =>
          joinedDocumentAnnotation
          |> JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.encode
          |> Utils.applyBs1(jsProps |> onShareClickedGet),
      ~onAddDocumentClicked=
        Utils.applyBs1(jsProps |> onAddDocumentClickedGet),
      [||],
    )
  );
