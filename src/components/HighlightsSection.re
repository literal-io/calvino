open Styles;

let component = ReasonReact.statelessComponent("HighlightsSection");

let make =
    (
      ~highlights,
      ~recentDocument,
      ~recentActivity,
      ~onPaginateHighlights,
      ~userProfileId,
      ~readerPath,
      _children,
    ) => {
  let renderProfile = _section =>
    <ProfileSection
      readerPath
      document=recentDocument
      activity=recentActivity
    />;
  let renderHighlights = section => {
    let highlights = section |> SectionList.TitledSection.dataGet;
    let items =
      highlights
      |> Js.Array.mapi((documentAnnotation, idx) =>
           <>
             <DocumentAnnotationTile
               onShareClicked={
                 () => Utils.shareDocumentAnnotation(~userProfileId, documentAnnotation)
               }
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
               annotationURL={
                 Utils.makeDocumentAnnotationURL(
                   ~readerPath,
                   ~document=
                     JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.target(
                       documentAnnotation,
                     ),
                   JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.source(
                     documentAnnotation,
                   ),
                 )
               }
             />
             {
               idx < Js.Array.length(highlights) - 1 ?
                 <div className={cn(["mv3"])} /> : ReasonReact.null
             }
           </>
         );
    <div className={cn(["flex", "flex-column", "mh2"])}> ...items </div>;
  };

  {
    ...component,
    render: _self =>
      <SectionList
        data=[|
          SectionList.TitledSection.make(~title="Profile", ~data=[||]),
          SectionList.TitledSection.make(
            ~title="Highlights",
            ~data=highlights,
          ),
        |]
        renderSectionHeader={
          section =>
            switch (section->SectionList.TitledSection.titleGet) {
            | "Highlights" =>
              <div className={cn(["mb4", "mh2", "pl", "b", "f2-r"])}>
                {
                  section
                  ->SectionList.TitledSection.titleGet
                  ->ReasonReact.string
                }
              </div>
            | "Profile" => ReasonReact.null
            | _ => ReasonReact.null
            }
        }
        renderSeparator={() => <div className={cn(["ma5"])} />}
        renderItem={
          section =>
            switch (section |> SectionList.TitledSection.titleGet) {
            | "Profile" => renderProfile(section)
            | "Highlights" => renderHighlights(section)
            | _ => ReasonReact.null
            }
        }
        onEndReached=onPaginateHighlights
        endThreshold=2.0
        renderInnerContainer={
          children =>
            <div className={cn(["ph5", "pv5", "bg-brand", "min-vh-100"])}>
              ...children
            </div>
        }
        renderLoadingIndicator={
          isLoadingMoreData =>
            <div
              className={
                cn([
                  "flex",
                  "flex-row",
                  "justify-center",
                  "items-center",
                  "bg-brand",
                  "pv5",
                ])
              }>
              <MaterialUi.CircularProgress
                variant=`Indeterminate
                size={`Int(48)}
                classes=[
                  MaterialUi.CircularProgress.Classes.Root(
                    cn([
                      "accent-100-o60",
                      "dn"->Cn.ifTrue(!isLoadingMoreData),
                    ]),
                  ),
                ]
              />
            </div>
        }
      />,
  };
};
