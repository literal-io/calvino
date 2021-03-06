let asJson = obj =>
  obj |> Js.Json.stringifyAny |> Js.Option.getExn |> Json.parseOrRaise;

let documentImageURLs = [|
  "https://www.googleapis.com/download/storage/v1/b/literal-images/o/1b20f630-c1b0-11e8-b634-240dbf38c455?generation=1537982275119337&alt=media",
  "https://www.googleapis.com/download/storage/v1/b/literal-images/o/ed8c09b0-c1b1-11e8-b634-240dbf38c455?generation=1537983057725228&alt=media",
  "https://www.googleapis.com/download/storage/v1/b/literal-images/o/15e02270-c1b2-11e8-b634-240dbf38c455?generation=1537983125314167&alt=media",
|];

let document = () =>
  JavamonnBsLibrarian.DocumentModel.(
    make(
      ~id=BsFaker.Random.uuid(),
      ~title=BsFaker.Lorem.words(~wordCount=Js.Math.random_int(10, 15), ()),
      ~author=BsFaker.Lorem.words(~wordCount=2, ()),
      ~numPages=string_of_int(Js.Math.random_int(100, 200)),
      ~fingerprint=BsFaker.Internet.mac(),
      ~originSource=
        OriginSource.{
          type_: `Web,
          url: Some(BsFaker.Internet.url()),
          id: None,
          httpHeaders: None,
          httpRequestBody: None,
          httpMethod: None,
        },
      ~source=Source.{type_: `Web, url: BsFaker.Internet.url()},
      ~documentImageURL=
        ImageURL.Source(
          documentImageURLs[Js.Math.random_int(
                              0,
                              Array.length(documentImageURLs),
                            )],
        ),
      (),
    )
  );

let documentAnnotation = () =>
  JavamonnBsLibrarian.DocumentAnnotationModel.make(
    ~id=BsFaker.Random.uuid(),
    ~documentId=BsFaker.Random.uuid(),
    ~userProfileId=BsFaker.Random.uuid(),
    ~descriptors=[||],
    ~text=
      BsFaker.Lorem.sentences(~sentenceCount=Js.Math.random_int(2, 5), ()),
    (),
  );

let documentOpenUserReadActivity = () =>
  JavamonnBsLibrarian.(
    UserReadActivityModel.DocumentOpen.make(
      ~documentId=BsFaker.Random.uuid(),
      ~owner=BsFaker.Random.uuid() |> LibrarianUtils.sha256,
      ~createdAt=Js.Date.make() |> Js.Date.toISOString,
      (),
    )
  );

let userDocument = () =>
  JavamonnBsLibrarian.UserDocumentModel.make(
    ~owner="",
    ~documentId=BsFaker.Random.uuid(),
    ~createdAt=Js.Date.make() |> Js.Date.toISOString,
    ~title=BsFaker.Lorem.words(~wordCount=Js.Math.random_int(10, 15), ()),
    ~author=BsFaker.Lorem.words(~wordCount=2, ()),
    (),
  );

module Js = {
  let document = () => document() |> JavamonnBsLibrarian.DocumentModel.encode;
  let documentAnnotation = () =>
    documentAnnotation() |> JavamonnBsLibrarian.DocumentAnnotationModel.encode;
};
