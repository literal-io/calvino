[@bs.val] external requireJSS: string => Js.Json.t = "require";
[@bs.val] external nodeEnv: string = "process.env.NODE_ENV";

let isDevelopment = nodeEnv !== "production";

/* doto operator, used to chain unit returning methods */
let ( *> ) = (x, f) => {
  let _ = f(x);
  x;
};

let wrapBs = cb => (. a) => cb(a);

let applyBs = (cb, ()) => cb(.);
let applyBs1 = (cb, a) => cb(. a);

let documentURLSource = document =>
  switch (JavamonnBsLibrarian.DocumentModel.ocrSource(document)) {
  | Some(ocrSource) =>
    ocrSource |> JavamonnBsLibrarian.DocumentModel.UrlSource.makeFromOcrSource
  | None =>
    document
    |> JavamonnBsLibrarian.DocumentModel.source
    |> JavamonnBsLibrarian.DocumentModel.UrlSource.makeFromSource(
         ~documentId=?JavamonnBsLibrarian.DocumentModel.id(document),
       )
  };

let makeDocumentURL = (~readerPath, document) =>
  document
  |> documentURLSource
  |> JavamonnBsLibrarian.DocumentModel.UrlSource.encode
  |> Qs.stringify
  |> (params => readerPath ++ "?" ++ params);

let makeDocumentAnnotationURL = (~readerPath, ~document, documentAnnotation) => {
  let urlSource = documentURLSource(document);
  let documentAnnotationId =
    documentAnnotation
    |> JavamonnBsLibrarian.DocumentAnnotationModel.id
    |> Js.Option.getExn;
  JavamonnBsLibrarian.DocumentModel.UrlSource.{
    ...urlSource,
    annotationId: Some(documentAnnotationId),
  }
  |> JavamonnBsLibrarian.DocumentModel.UrlSource.encode
  |> Qs.stringify
  |> (params => readerPath ++ "?" ++ params);
};

let shareDocumentAnnotation = (~userProfileId, documentAnnotation) =>
  if (isDevelopment) {
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

