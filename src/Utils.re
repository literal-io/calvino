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

let pathCombine = (p1, p2) => {
  let lastCharP1 = Js.String.charAt(Js.String.length(p1) - 1, p1);
  let firstCharP2 = Js.String.charAt(0, p2);
  switch (lastCharP1, firstCharP2) {
  | ("/", "/") => p1 ++ Js.String.substr(1, p2)
  | ("/", _)
  | (_, "/") => p1 ++ p2
  | (_, _) => p1 ++ "/" ++ p2
  };
};

let documentURLSource = document =>
  switch (JavamonnBsLibrarian.DocumentModel.ocrSource(document)) {
  | Some(ocrSource) =>
    ocrSource
    |> JavamonnBsLibrarian.DocumentModel.UrlSource.makeFromOcrSource(
         ~documentId=?JavamonnBsLibrarian.DocumentModel.id(document),
       )
  | None =>
    document
    |> JavamonnBsLibrarian.DocumentModel.source
    |> JavamonnBsLibrarian.DocumentModel.UrlSource.makeFromSource(
         ~documentId=?JavamonnBsLibrarian.DocumentModel.id(document),
       )
  };

let makeDocumentURL = (~readerPath, ~documentDetail=false, document) => {
  let basePath =
    documentDetail ?
      pathCombine(readerPath, "document-detail") ++ "?" : readerPath ++ "?";

  document
  |> documentURLSource
  |> JavamonnBsLibrarian.DocumentModel.UrlSource.encode
  |> Qs.stringify
  |> (params => basePath ++ params);
};

let makeDocumentAnnotationURL =
    (~readerPath, ~documentDetail=false, ~document, documentAnnotation) => {
  let urlSource = documentURLSource(document);
  let documentAnnotationId =
    documentAnnotation
    |> JavamonnBsLibrarian.DocumentAnnotationModel.id
    |> Js.Option.getExn;
  let basePath =
    documentDetail ?
      pathCombine(readerPath, "document-detail") ++ "?" : readerPath ++ "?";
  JavamonnBsLibrarian.DocumentModel.UrlSource.{
    ...urlSource,
    annotationId: Some(documentAnnotationId),
    documentId: JavamonnBsLibrarian.DocumentModel.id(document),
  }
  |> JavamonnBsLibrarian.DocumentModel.UrlSource.encode
  |> Qs.stringify
  |> (params => basePath ++ params);
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
    JavamonnBsLibrarian.FindService.UserReadActivity.findOrCreate(
      ~query=
        JavamonnBsLibrarian.LibrarianFind.makeQ(
          ~type_=
            `DocumentShare
            |> JavamonnBsLibrarian.UserReadActivityModel.activityTypeToJs
            |> Js.Nullable.return,
          ~documentId=documentId |> Js.Nullable.return,
          ~owner=
            userProfileId
            |> JavamonnBsLibrarian.LibrarianUtils.sha256
            |> Js.Nullable.return,
          (),
        ),
      ~creator=
        () =>
          JavamonnBsLibrarian.UserReadActivityModel.make(
            ~type_=`DocumentShare,
            ~documentId,
            ~userProfileId,
            (),
          )
          |> Vow.Result.return,
      (),
    )
    |> Vow.Result.map(_result => ());
  };
