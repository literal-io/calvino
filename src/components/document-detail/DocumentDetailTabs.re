open Styles;

type state = {activeIdx: int};

type action =
  | SetIdx(int);

let component = ReasonReact.reducerComponent("DocumentDetailTabs");

let make =
    (
      ~documentAnnotations,
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
        classes=[MaterialUi.Tabs.Classes.Indicator(cn(["bg-accent"]))]>
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
      <div className={cn(["flex", "flex-auto", "relative", "items-center"])}>
        {self.state.activeIdx == 0 ?
           <DocumentActivity /> :
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
