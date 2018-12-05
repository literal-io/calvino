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
          FindService.makeQuery(
            ~_type=UserReadActivityModel.activityTypeToJs(`DocumentShare),
            ~documentId,
            ~owner=LibrarianUtils.sha256(userProfileId),
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
  ...component,
  render: _self =>
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
                   <DocumentAnnotationTile
                     onShareClicked={
                       () =>
                         handleShareClicked(
                           ~userProfileId,
                           documentAnnotation,
                         )
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
          <div className={cn(["flex", "flex-column", "mh2"])}>
            ...items
          </div>;
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
