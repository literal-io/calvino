open Styles;
let component = ReasonReact.statelessComponent("DashboardScreen");

let renderLibrarySection =
    (~documents, ~onPaginateDocuments, ~onDocumentClicked, ()) =>
  <SectionList
    data=[|
      SectionList.TitledSection.make(~title="Library", ~data=documents),
    |]
    renderSectionHeader={
      section =>
        <div className={cn(["mb4", "pd", "b", "f3", "flex", "flex-auto"])}>
          {section->SectionList.TitledSection.titleGet->ReasonReact.string}
        </div>
    }
    renderSeparator={() => ReasonReact.null}
    renderItem={
      section =>
        <DocumentTileMasonryGrid
          data={section->SectionList.TitledSection.dataGet}
          columns=3
          gutter=32
        />
    }
    onEndReached=onPaginateDocuments
    endThreshold=2.0
    renderInnerContainer={
      children =>
        <div className={cn(["ph4", "pt5", "flex", "items-center", "flex-column"])}>
          <div>
            ...children
          </div>
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
        <div className={cn(["mb4", "pl", "b", "f3"])}>
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
        <div className={cn(["flex", "flex-column"])}> ...items </div>;
      }
    }
    onEndReached=onPaginateHighlights
    endThreshold=2.0
    renderInnerContainer={
      children =>
        <div className={cn(["ph4", "pt5", "bg-brand"])}> ...children </div>
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
