open Styles;

type state = {activeIdx: int};

type action =
  | SetIdx(int);

let component = ReasonReact.reducerComponent("DocumentDetailTabs");

let make =
    (
      ~document,
      ~documentAnnotations,
      ~firstDocumentOpenActivity,
      ~lastDocumentOpenActivity,
      ~onPaginateDocumentAnnotations,
      ~onDocumentAnnotationTileShare,
      ~onDocumentAnnotationTileClick,
      ~userProfileId,
      ~readerPath,
      _children,
    ) => {
  ...component,
  initialState: () => {activeIdx: 0},
  reducer: (action, state) =>
    switch (action) {
    | SetIdx(activeIdx) => ReasonReact.Update({activeIdx: activeIdx})
    },
  render: self =>
    <div className={cn(["flex", "flex-auto", "flex-column"])}>
      <MaterialUi.Tabs
        value={self.state.activeIdx}
        onChange={(_ev, idx) => self.send(SetIdx(idx))}
        variant=`FullWidth
        classes=[
          Root(cn(["z-1", "mui-shadow-3", "bg-brand"])),
          Indicator(cn(["bg-accent"])),
        ]>
        <MaterialUi.Tab
          label={
            <span className={cn(["pl"])}>
              {ReasonReact.string("Activity")}
            </span>
          }
        />
        <MaterialUi.Tab
          label={
            <span className={cn(["pl"])}>
              {ReasonReact.string("Highlights")}
            </span>
          }
        />
      </MaterialUi.Tabs>
      <div className={cn(["flex", "flex-auto", "relative", "items-center", "bg-gray"])}>
        {self.state.activeIdx == 0 ?
           <DocumentDetailActivity
             firstDocumentOpenActivity
             lastDocumentOpenActivity
             document
           /> :
           <DocumentAnnotationsList
             documentAnnotations
             onPaginateDocumentAnnotations
             onDocumentAnnotationTileClick
             onDocumentAnnotationTileShare
             userProfileId
             readerPath
             hideDocumentInfo=true
           />}
      </div>
    </div>,
};
