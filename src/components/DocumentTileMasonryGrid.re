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
  src: string,
  element: Webapi.Dom.HtmlImageElement.t,
  size: option(size),
  hasLoaded: bool,
};

type state = {
  images: Images.t(image),
  containerRef: ref(option(Dom.element)),
  bricks: ref(option(Bricks.t)),
};

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

let handleUpdate = bricks =>
  bricks |> Js.Option.map(Utils.wrapBs(Bricks.update));

let handleContainerRef =
    (~columns, ~gutter, containerRef, {ReasonReact.state}) =>
  switch (state.containerRef^, Js.Nullable.toOption(containerRef)) {
  | (None, Some(containerRef)) =>
    state.containerRef := Some(containerRef);
    let bricks =
      Bricks.(
        Params.make(
          ~container=containerRef,
          ~packed="packed",
          ~sizes=[|Params.makeSize(~columns, ~gutter, ())|],
        )
        |> make
      );
    let _ = Bricks.pack(bricks);
    state.bricks := Some(bricks);
    ();
  | _ => () /* Bricks initialized, noop */
  };

let make = (~data, ~columns, ~gutter, _children) => {
  ...component,
  initialState: () => {
    images: Images.empty,
    bricks: ref(None),
    containerRef: ref(None),
  },
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
                  src,
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
        {...state, images: updatedImages},
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
                     );
                     let _ = Webapi.Dom.HtmlImageElement.setSrc(element, src);
                     ();
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
          ...state,
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
  didUpdate: ({newSelf}) => {
    let _ = handleUpdate(newSelf.state.bricks^);
    ();
  },
  render: self => {
    let renderDocumentTile = (~image=?, document) =>
      switch (image) {
      | Some({src, size: Some({height})}) =>
        <DocumentTile
          title={JavamonnBsLibrarian.DocumentModel.title(document)}
          author={JavamonnBsLibrarian.DocumentModel.author(document)}
          imageURL=src
          imageHeight=height
        />
      | _ =>
        <DocumentTile
          title={JavamonnBsLibrarian.DocumentModel.title(document)}
          author={JavamonnBsLibrarian.DocumentModel.author(document)}
        />
      };
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
              | image when image.hasLoaded == true =>
                Array.append(memo, [|renderDocumentTile(~image, document)|])
              | _ =>
                shouldContinueRendering := false;
                memo;
              | exception Not_found =>
                shouldContinueRendering := false;
                memo;
              }
            | None => Array.append(memo, [|renderDocumentTile(document)|])
            };
          },
        [||],
        data,
      );
    <div ref={self.handle(handleContainerRef(~columns, ~gutter))}>
      ...documentTiles
    </div>;
  },
};
