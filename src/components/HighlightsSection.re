open Styles;

let component = ReasonReact.statelessComponent("HighlightsSection");

let handleShareClicked = (~userProfileId, documentAnnotation) =>
  if (Utils.isDevelopment) {
    Vow.Result.return();
  } else {
    let documentAnnotationId =
      documentAnnotation
      |> JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.source
      |> JavamonnBsLibrarian.DocumentAnnotationModel.id
      |> Js.Option.getExn;
    let documentId =
      documentAnnotation
      |> JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.target
      |> JavamonnBsLibrarian.DocumentModel.id
      |> Js.Option.getExn;
    /** Asynchronously share the document if it is not already shared. */
    JavamonnBsLibrarian.(
      FindService.UserReadActivity.findOrCreate(
        ~query=
          LibrarianFind.makeQ(
            ~type_=
              `DocumentShare
              |> UserReadActivityModel.activityTypeToJs
              |> Js.Nullable.return,
            ~documentId=documentId |> Js.Nullable.return,
            ~owner=
              userProfileId |> LibrarianUtils.sha256 |> Js.Nullable.return,
            (),
          ),
        ~creator=
          () =>
            JavamonnBsLibrarian.UserReadActivityModel.(
              make(~type_=`DocumentShare, ~documentId, ~userProfileId, ())
            )
            |> Vow.Result.return,
        (),
      )
    )
    |> Vow.Result.map(_result => ());
  };

let make =
    (
      ~highlights,
      ~onPaginateHighlights,
      ~userProfileId,
      ~readerPath,
      _children,
    ) => {
  let renderProfile = _section =>
    <ProfileSection
      readerPath
      document={Mocks.document()}
      activity=ProfileSection.{
        documentsCreated: Js.Math.random_int(8, 40),
        highlightsCreated: Js.Math.random_int(8, 4),
        pagesRead: Js.Math.random_int(20, 120),
      }
    />;
  let renderHighlights = section => {
    let highlights = section |> SectionList.TitledSection.dataGet;
    let items =
      highlights
      |> Js.Array.mapi((documentAnnotation, idx) =>
           <>
             <DocumentAnnotationTile
               onShareClicked={
                 () => handleShareClicked(~userProfileId, documentAnnotation)
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
      />,
  };
};
