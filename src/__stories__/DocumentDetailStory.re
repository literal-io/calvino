open BsStorybook.Story;
open Styles;
open StoryUtils;

let _module = [%bs.raw "module"];

storiesOf("DocumentDetail", _module)
->(
    add("DocumentDetailNavBar", () =>
      <AppFrame style={make(~width=px(400), ())}>
        <DocumentDetailNavBar onBack={() => ()} onMinimize={() => ()} />
      </AppFrame>
    )
  )
->(
    add("DocumentDetailHeader", () => {
      let document = Mocks.document();
      <AppFrame style={make(~width=px(500), ())}>
        <DocumentDetailHeader
          title={
            document
            |> JavamonnBsLibrarian.DocumentModel.title
            |> Js.Option.some
          }
          author={
            document
            |> JavamonnBsLibrarian.DocumentModel.author
            |> Js.Option.some
          }
          onTitleChange={v => Js.log2("onTitleChange", v)}
          onAuthorChange={v => Js.log2("onAuthorChange", v)}
        />
      </AppFrame>;
    })
  )
->(
    add("DocumentDetailActionButtons", () => {
      let document = Mocks.document();
      <AppFrame style={make(~width=px(500), ())}>
        <DocumentDetailActionButtons
          onShare={() => Js.log("onShare")}
          onSave={() => Js.log("onSave")}
          onDelete={() => Js.log("onDelete")}
          onGetDocumentShareClipboardText={() =>
            "onGetDocumentShareClipboardText"
          }
        />
      </AppFrame>;
    })
  )
->(
    add("DocumentDetailTabs", () =>
      <AppFrame
        className={cn(["pa0", "bg-brand", "ff-r"])}
        style={make(~width=px(500), ~height=px(800), ~display="flex", ())}>
        <DocumentDetailTabs
          document={Some(Mocks.document())}
          firstDocumentOpenActivity={
            Some(Mocks.documentOpenUserReadActivity())
          }
          lastDocumentOpenActivity={
            Some(Mocks.documentOpenUserReadActivity())
          }
          documentAnnotations={Array.init(20, _idx =>
            JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.make(
              ~source=Mocks.documentAnnotation(),
              ~target=Mocks.document(),
              (),
            )
          )}
          onPaginateDocumentAnnotations={() =>
            Js.Promise.make((~resolve as _resolve, ~reject as _reject) => ())
            |> Js.Nullable.return
          }
          onDocumentAnnotationTileClick={(~annotationUrl, ~documentAnnotation) =>
            Js.log2("onDocumentAnnotationTileClick", annotationUrl)
          }
          onDocumentAnnotationTileShare={() =>
            Js.log("onDocumentAnnotationTileShare")
          }
          userProfileId={BsFaker.Random.uuid()}
          readerPath="http://localhost:9001"
        />
      </AppFrame>
    )
  )
->(
    add("DocumentDetail", () =>
      <AppFrame
        className={cn(["pa0", "bg-brand", "ff-r"])}
        style={make(~width=px(500), ~height=px(800), ~display="flex", ())}>
        <DocumentDetail
          document={Some(Mocks.document())}
          userDocument={Some(Mocks.userDocument())}
          documentAnnotations={Array.init(20, _idx =>
            JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.make(
              ~source=Mocks.documentAnnotation(),
              ~target=Mocks.document(),
              (),
            )
          )}
          onPaginateDocumentAnnotations={() =>
            Js.Promise.make((~resolve as _resolve, ~reject as _reject) => ())
            |> Js.Nullable.return
          }
          onDocumentAnnotationTileClick={(~annotationUrl, ~documentAnnotation) =>
            Js.log2("onDocumentAnnotationTileClick", annotationUrl)
          }
          onDocumentAnnotationTileShare={() =>
            Js.log("onDocumentAnnotationTileShare")
          }
          onTitleChange={v => Js.log2("onTitleChange", v)}
          onAuthorChange={v => Js.log2("onAuthorChange", v)}
          onDocumentShare={() => Js.log("onDocumentShare")}
          onDocumentDelete={() => Js.log("onDocumentDelete")}
          onDocumentSave={() => Js.log("onDocumentSave")}
          onMinimize={() => Js.log("onMinimize")}
          onBack={() => Js.log("onBack")}
          userProfileId={BsFaker.Random.uuid()}
          firstDocumentOpenActivity={
            Some(Mocks.documentOpenUserReadActivity())
          }
          lastDocumentOpenActivity={
            Some(Mocks.documentOpenUserReadActivity())
          }
          readerPath="http://localhost:9001"
        />
      </AppFrame>
    )
  )
->(
    add("Loading DocumentDetail", () =>
      <AppFrame
        className={cn(["pa0", "bg-brand", "ff-r"])}
        style={make(~width=px(500), ~height=px(800), ~display="flex", ())}>
        <DocumentDetail
          document=None
          userDocument=None
          documentAnnotations={Array.init(20, _idx =>
            JavamonnBsLibrarian.JoinedModel.DocumentAnnotationToDocument.make(
              ~source=Mocks.documentAnnotation(),
              ~target=Mocks.document(),
              (),
            )
          )}
          onPaginateDocumentAnnotations={() =>
            Js.Promise.make((~resolve as _resolve, ~reject as _reject) => ())
            |> Js.Nullable.return
          }
          onDocumentAnnotationTileClick={(~annotationUrl, ~documentAnnotation) =>
            Js.log2("onDocumentAnnotationTileClick", annotationUrl)
          }
          onDocumentAnnotationTileShare={() =>
            Js.log("onDocumentAnnotationTileShare")
          }
          onTitleChange={v => Js.log2("onTitleChange", v)}
          onAuthorChange={v => Js.log2("onAuthorChange", v)}
          onDocumentShare={() => Js.log("onDocumentShare")}
          onDocumentDelete={() => Js.log("onDocumentDelete")}
          onDocumentSave={() => Js.log("onDocumentSave")}
          onMinimize={() => Js.log("onMinimize")}
          onBack={() => Js.log("onBack")}
          userProfileId={BsFaker.Random.uuid()}
          firstDocumentOpenActivity=None
          lastDocumentOpenActivity=None
          readerPath="http://localhost:9001"
        />
      </AppFrame>
    )
  );
