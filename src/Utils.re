[@bs.val] external requireJSS: string => Js.Json.t = "require";
[@bs.val] external nodeEnv : string = "process.env.NODE_ENV"

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
    |> JavamonnBsLibrarian.DocumentModel.UrlSource.makeFromSource
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
