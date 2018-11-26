open Styles;
let component = ReasonReact.statelessComponent("DashboardScreen");

module JoinedDocumentAnnotation =
  JavamonnBsLibrarian.JoinedModel.Make(
    JavamonnBsLibrarian.DocumentAnnotationModel,
    JavamonnBsLibrarian.DocumentModel,
    {
      let joinedOn = "document";
    },
  );

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
    <div className={cn(["flex", "flex-row", "flex-auto"])}>
      <SectionList
        data=[|
          SectionList.TitledSection.make(~title="Library", ~data=documents),
        |]
        renderSectionHeader={
          section =>
            <div className={cn(["mv3", "pd", "b", "f3"])}>
              {section->SectionList.TitledSection.titleGet->ReasonReact.string}
            </div>
        }
        renderSeparator={() => ReasonReact.null}
        renderItem={
          section =>
            <MasonryGrid
              data={section->SectionList.TitledSection.dataGet}
              renderItem={
                document =>
                  <DocumentTile
                    title={JavamonnBsLibrarian.DocumentModel.title(document)}
                    author={
                      JavamonnBsLibrarian.DocumentModel.author(document)
                    }
                    imageURL={
                      JavamonnBsLibrarian.DocumentModel.(
                        document
                        |> imageURL
                        |> Js.Option.map((. imageURL) => 
                            switch (imageURL) {
                              | ImageURL.Source(source) => source
                              | ImageURL.Processed({ w200 }) => w200
                            }
                          )
                      )
                    }
                  />
              }
              columns=3
              gutter=32
            />
        }
        onEndReached=onPaginateDocuments
        endThreshold=2.0
        renderInnerContainer={
          children => <div className={cn(["mh4"])}> ...children </div>
        }
      />
      <SectionList
        data=[|
          SectionList.TitledSection.make(
            ~title="Highlights",
            ~data=highlights,
          ),
        |]
        renderSectionHeader={
          section =>
            <div className={cn(["mv3", "pl", "b", "f3"])}>
              {section->SectionList.TitledSection.titleGet->ReasonReact.string}
            </div>
        }
        renderSeparator={() => ReasonReact.null}
        renderItem={
          section => {
            let highlights = section |> SectionList.TitledSection.dataGet;
            let items =
              highlights
              |> Js.Array.mapi((highlight, idx) => {
                   let documentAnnotation =
                     highlight |> JoinedDocumentAnnotation.decode;
                   <>
                     <HighlightListItem
                       onShareClicked
                       title={
                         documentAnnotation
                         |> Js.Option.map((. highlight) =>
                              highlight
                              |> JoinedDocumentAnnotation.target
                              |> JavamonnBsLibrarian.DocumentModel.title
                            )
                         |> Js.Option.getWithDefault("Unknown Title")
                       }
                       author={
                         documentAnnotation
                         |> Js.Option.map((. highlight) =>
                              highlight
                              |> JoinedDocumentAnnotation.target
                              |> JavamonnBsLibrarian.DocumentModel.author
                            )
                         |> Js.Option.getWithDefault("Unknown Author")
                       }
                       text={
                         documentAnnotation
                         |> Js.Option.andThen((. highlight) =>
                              highlight
                              |> JoinedDocumentAnnotation.source
                              |> JavamonnBsLibrarian.DocumentAnnotationModel.text
                            )
                         |> Js.Option.getWithDefault("")
                       }
                     />
                     {
                       idx < Js.Array.length(highlights) - 1 ?
                         <div className={cn(["mv2"])} /> : ReasonReact.null
                     }
                   </>;
                 });
            <div className={cn(["flex", "flex-column"])}> ...items </div>;
          }
        }
        onEndReached=onPaginateHighlights
        endThreshold=2.0
        renderInnerContainer={
          children => <div className={cn(["mh3"])}> ...children </div>
        }
      />
    </div>,
};
