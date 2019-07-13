open Styles;

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
  shouldUpdateBricks: ref(bool),
};

type actions =
  | LoadImagesBegin(array(JavamonnBsLibrarian.DocumentModel.t))
  | LoadImageComplete((string, size));

let component = ReasonReact.reducerComponent("DocumentTileMasonryGrid");

let documentImageURL = document =>
  JavamonnBsLibrarian.DocumentModel.(
    switch (documentImageURL(document)) {
    | Some(ImageURL.Source(src)) => Some(src)
    | Some(ImageURL.Processed({w200, source})) => Some(source)
    | None => None
    }
  );

let handleUpdate =
  Lodash.throttle(
    (. bricks) => bricks |> Js.Option.map(Utils.wrapBs(Bricks.update)),
    300,
  );

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

let make =
    (~data, ~columns, ~gutter, ~readerPath, ~onDocumentTileClick=?, _children) => {
  ...component,
  initialState: () => {
    images: Images.empty,
    bricks: ref(None),
    containerRef: ref(None),
    shouldUpdateBricks: ref(false),
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
      if (Js.Array.length(imageSourcesToLoad) == 0) {
        ReasonReact.NoUpdate;
      } else {
        ReasonReact.UpdateWithSideEffects(
          {...state, images: updatedImages},
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
                            /** Scale the image, preserving aspect ratio, if required */
                            let renderedHeight =
                              width > 200 ?
                                int_of_float(
                                  float_of_int(height)
                                  /. float_of_int(width)
                                  *. 200.0,
                                ) :
                                height;
                            self.send(
                              LoadImageComplete((
                                src,
                                {width, height: renderedHeight},
                              )),
                            );
                          })
                     );
                     let _ = Webapi.Dom.HtmlImageElement.setSrc(element, src);
                     ();
                   | exception Not_found => ()
                   }
                 );
            ();
          },
        );
      };
    | LoadImageComplete((src, size)) =>
      switch (Images.find(src, state.images)) {
      | image =>
        ReasonReact.Update({
          ...state,
          shouldUpdateBricks: ref(true),
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
  shouldUpdate: ({oldSelf, newSelf}) =>
    Images.exists(
      (src, {hasLoaded}) => {
        let oldHasLoaded =
          switch (Images.find(src, oldSelf.state.images)) {
          | {hasLoaded} => hasLoaded
          | exception Not_found => false
          };
        hasLoaded && !oldHasLoaded;
      },
      newSelf.state.images,
    ),
  didUpdate: ({oldSelf, newSelf}) => {
    let _ =
      if (newSelf.state.images !== oldSelf.state.images
          && newSelf.state.shouldUpdateBricks^) {
        newSelf.state.shouldUpdateBricks := false;
        let _ = handleUpdate(. newSelf.state.bricks^);
        ();
      };
    ();
  },
  render: self => {
    let renderDocumentTile = (~image=?, document) =>
      switch (image) {
      | Some({src, size: Some({height})}) =>
        <DocumentTile
          className={cn(["vh-packed", "absolute"])}
          title={JavamonnBsLibrarian.DocumentModel.title(document)}
          author={JavamonnBsLibrarian.DocumentModel.author(document)}
          imageURL=src
          imageHeight=height
          onClick=?onDocumentTileClick
          documentURL={Utils.makeDocumentURL(
            ~readerPath,
            ~documentDetail=true,
            document,
          )}
        />
      | _ =>
        <DocumentTile
          className={cn(["vh-packed", "absolute"])}
          title={JavamonnBsLibrarian.DocumentModel.title(document)}
          author={JavamonnBsLibrarian.DocumentModel.author(document)}
          onClick=?onDocumentTileClick
          documentURL={Utils.makeDocumentURL(
            ~readerPath,
            ~documentDetail=true,
            document,
          )}
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
    <div
      ref={self.handle(handleContainerRef(~columns, ~gutter))}
      style={make(~width=px(200 * 3 + gutter * 2), ())}>
      ...documentTiles
    </div>;
  },
};
