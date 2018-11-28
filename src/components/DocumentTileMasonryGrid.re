/**
 * MasonryGrid with support for deferring Bricks.js reflowing until children tiles
 * have loaded images and settled height.
 */
module Images = Map.Make(String);

type size = {
  width: int,
  height: int,
};

type image = {
  element: Webapi.Dom.HtmlImageElement.t,
  size: option(size),
  hasLoaded: bool,
};

type state = {images: Images.t(image)};

type actions =
  | LoadImagesBegin(array(JavamonnBsLibrarian.DocumentModel.t))
  | LoadImageComplete((string, size));

let component = ReasonReact.reducerComponent("DocumentTileMasonryGrid");

let documentImageURL = document =>
  JavamonnBsLibrarian.DocumentModel.(
    switch (documentImageURL(document)) {
    | Some(ImageURL.Source(src)) => Some(src)
    | Some(ImageURL.Processed({w200})) => Some(w200)
    | None => None
    }
  );

let make = (~data, ~columns, ~gutter, _children) => {
  ...component,
  initialState: () => {images: Images.empty},
  reducer: (action, state) =>
    switch (action) {
    | LoadImagesBegin(data) =>
      let imageSourcesToLoad =
        data
        |> Array.map(documentImageURL)
        |> Js.Array.filter(Js.Option.isSome)
        |> Array.map(Js.Option.getExn);

      let updatedImages =
        Js.Array.reduce(
          (images, src) =>
            switch (Images.find(src, images)) {
            | _binding => images
            | exception Not_found =>
              Images.add(
                src,
                {
                  element: Webapi.Dom.HtmlImageElement.make(),
                  hasLoaded: false,
                  size: None,
                },
                images,
              )
            },
          state.images,
          imageSourcesToLoad,
        );
      ReasonReact.UpdateWithSideEffects(
        {images: updatedImages},
        (
          self => {
            let _ =
              imageSourcesToLoad
              |> Js.Array.forEach(src =>
                   switch (Images.find(src, self.state.images)) {
                   | {element} =>
                     Webapi.Dom.(
                       element
                       |> HtmlImageElement.addEventListener("load", _ev => {
                            let width = HtmlImageElement.width(element);
                            let height = HtmlImageElement.height(element);
                            self.send(
                              LoadImageComplete((src, {width, height})),
                            );
                          })
                     )
                   | exception Not_found => ()
                   }
                 );
            ();
          }
        ),
      );
    | LoadImageComplete((src, size)) =>
      switch (Images.find(src, state.images)) {
      | image =>
        ReasonReact.Update({
          images:
            Images.add(
              src,
              {...image, size: Some(size), hasLoaded: true},
              state.images,
            ),
        })
      | exception Not_found => ReasonReact.NoUpdate
      }
    },
  didMount: self => {
    self.send(LoadImagesBegin(data));
    ();
  },
  willReceiveProps: self => {
    self.send(LoadImagesBegin(data));
    self.state;
  },
  render: self => {
    let shouldContinueRendering = ref(true);
    let documentTiles =
      Js.Array.reduce(
        (memo, document) =>
          if (! shouldContinueRendering^) {
            memo;
          } else {
            switch (documentImageURL(document)) {
            | Some(source) =>
              switch (Images.find(source, self.state.images)) {
              | image => memo @@ [|renderDocumentTile(~image, document)|]
              | exception Not_found => memo
              }
            | None => memo @@ [|renderDocumentTile(document)|]
            };
          },
        [||],
        data,
      );
    ();
  },
};
