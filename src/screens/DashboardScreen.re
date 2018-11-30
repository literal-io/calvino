open Styles;
let component = ReasonReact.statelessComponent("DashboardScreen");

let renderLibrarySection =
    (
      ~documents,
      ~onPaginateDocuments,
      ~onDocumentClicked,
      ~onAddDocumentClicked,
      (),
    ) =>
  <SectionList
    data=[|
      SectionList.TitledSection.make(~title="Library", ~data=documents),
    |]
    renderSectionHeader={
      section =>
        <div
          className={
            cn([
              "mb5",
              "flex",
              "flex-auto",
              "justify-between",
              "items-center",
            ])
          }>
          <span className={cn(["pd", "b", "f2-r"])}>
            {section->SectionList.TitledSection.titleGet->ReasonReact.string}
          </span>
          <MaterialUi.IconButton onClick={_ev => onAddDocumentClicked()}>
            <MaterialIcon.Add
              style={
                make(~width=px(37), ~height=px(37), ~fontSize=px(37), ())
              }
            />
          </MaterialUi.IconButton>
        </div>
    }
    renderSeparator={() => ReasonReact.null}
    renderItem={
      section =>
        <DocumentTileMasonryGrid
          data={section->SectionList.TitledSection.dataGet}
          columns=3
          gutter=42
        />
    }
    onEndReached=onPaginateDocuments
    endThreshold=2.0
    renderInnerContainer={
      children =>
        <div
          className={
            cn([
              "ph4",
              "pt5",
              "flex",
              "items-center",
              "flex-column",
              "bg-gray",
            ])
          }>
          <div> ...children </div>
        </div>
    }
  />;

let renderHighlightsSection =
    (
      ~highlights,
      ~onShareClicked,
      ~onPaginateHighlights,
      ~onHighlightClicked,
      (),
    ) =>
  <SectionList
    data=[|
      SectionList.TitledSection.make(~title="Highlights", ~data=highlights),
    |]
    renderSectionHeader={
      section =>
        <div className={cn(["mb5", "mh2", "pl", "b", "f2-r"])}>
          {section->SectionList.TitledSection.titleGet->ReasonReact.string}
        </div>
    }
    renderSeparator={() => ReasonReact.null}
    renderItem={
      section => {
        let highlights = section |> SectionList.TitledSection.dataGet;
        let items =
          highlights
          |> Js.Array.mapi((documentAnnotation, idx) =>
               <>
                 <HighlightListItem
                   onShareClicked
                   title={
                     documentAnnotation
                     |> Js.Option.map((. highlight) =>
                          JavamonnBsLibrarian.(
                            highlight
                            |> JoinedModel.DocumentAnnotationToDocument.target
                            |> DocumentModel.title
                          )
                        )
                     |> Js.Option.getWithDefault("Unknown Title")
                   }
                   author={
                     documentAnnotation
                     |> Js.Option.map((. highlight) =>
                          JavamonnBsLibrarian.(
                            highlight
                            |> JoinedModel.DocumentAnnotationToDocument.target
                            |> DocumentModel.author
                          )
                        )
                     |> Js.Option.getWithDefault("Unknown Author")
                   }
                   text={
                     documentAnnotation
                     |> Js.Option.andThen((. highlight) =>
                          JavamonnBsLibrarian.(
                            highlight
                            |> JoinedModel.DocumentAnnotationToDocument.source
                            |> DocumentAnnotationModel.text
                          )
                        )
                     |> Js.Option.getWithDefault("")
                   }
                 />
                 {
                   idx < Js.Array.length(highlights) - 1 ?
                     <div className={cn(["mv2"])} /> : ReasonReact.null
                 }
               </>
             );
        <div className={cn(["flex", "flex-column", "mh2"])}> ...items </div>;
      }
    }
    onEndReached=onPaginateHighlights
    endThreshold=2.0
    renderInnerContainer={
      children =>
        <div className={cn(["ph5", "pt5", "bg-brand"])}> ...children </div>
    }
  />;

let make =
    (
      ~documents,
      ~highlights,
      ~onPaginateDocuments,
      ~onPaginateHighlights,
      ~onShareClicked,
      ~onDocumentClicked,
      ~onAddDocumentClicked,
      ~onHighlightClicked,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div className={cn(["flex", "flex-row", "flex-auto", "ff-r"])}>
      <div className={cn(["relative", "flex-2"])}>
        {
          renderLibrarySection(
            ~documents,
            ~onPaginateDocuments,
            ~onDocumentClicked,
            ~onAddDocumentClicked,
            (),
          )
        }
      </div>
      <div className={cn(["relative", "flex-1"])}>
        {
          renderHighlightsSection(
            ~highlights,
            ~onPaginateHighlights,
            ~onShareClicked,
            ~onHighlightClicked,
            (),
          )
        }
      </div>
    </div>,
};

[@bs.deriving abstract]
type jsProps = {
  documents: Js.Array.t(Js.Json.t),
  highlights: Js.Array.t(Js.Json.t),
  onPaginateDocuments: (. unit) => Js.Nullable.t(Js.Promise.t(unit)),
  onPaginateHighlights: (. unit) => Js.Nullable.t(Js.Promise.t(unit)),
  onShareClicked: (. Js.Json.t) => unit,
  onDocumentClicked: (. Js.Json.t) => unit,
  onHighlightClicked: (. Js.Json.t) => unit,
  onAddDocumentClicked: (. unit) => unit,
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
           ),
      ~onPaginateDocuments=Utils.applyBs(jsProps |> onPaginateDocumentsGet),
      ~onPaginateHighlights=Utils.applyBs(jsProps |> onPaginateHighlightsGet),
      ~onShareClicked=
        joinedDocumentAnnotation =>
          joinedDocumentAnnotation
          |> JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.encode
          |> Utils.applyBs(jsProps |> onShareClickedGet),
      ~onDocumentClicked=
        document =>
          document
          |> JavamonnBsLibrarian.DocumentModel.decode
          |> Utils.applyBs(jsProps |> onDocumentClickedGet),
      ~onHighlightClicked=
        joinedDocumentAnnotation =>
          joinedDocumentAnnotation
          |> JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.encode
          |> Utils.applyBs(jsProps |> onHighlightClickedGet),
      ~onAddDocumentClicked=Utils.applyBs(jsProps |> onAddDocumentClickedGet),
      [||],
    )
  );
