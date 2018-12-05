open Styles;

let component = ReasonReact.statelessComponent("LibrarySection");

let make =
    (
      ~documents,
      ~onPaginateDocuments,
      ~onAddDocumentClicked,
      ~readerPath,
      _children,
    ) => {
  ...component,
  render: _self =>
    <SectionList
      data=[|
        SectionList.TitledSection.make(~title="Library", ~data=documents),
      |]
      renderSectionHeader={
        section =>
          <div
            className={
              cn([
                "mb5",
                "flex",
                "flex-auto",
                "justify-between",
                "items-center",
              ])
            }>
            <span className={cn(["pd", "b", "f2-r"])}>
              {section->SectionList.TitledSection.titleGet->ReasonReact.string}
            </span>
            <IconMenuButton
              renderIcon={
                () =>
                  <MaterialIcon.Add
                    style={
                      make(
                        ~width=px(32),
                        ~height=px(32),
                        ~fontSize=px(32),
                        (),
                      )
                    }
                  />
              }
              renderMenuItems={
                (~onClick, ()) => [|
                  <MaterialUi.MenuItem
                    onClick={
                      _ev => {
                        onClick();
                        onAddDocumentClicked("drive");
                      }
                    }>
                    {ReasonReact.string("Open from Google Drive")}
                  </MaterialUi.MenuItem>,
                  <MaterialUi.MenuItem
                    onClick={
                      _ev => {
                        onClick();
                        onAddDocumentClicked("dropbox");
                      }
                    }>
                    {ReasonReact.string("Open from Dropbox")}
                  </MaterialUi.MenuItem>,
                |]
              }
            />
          </div>
      }
      renderSeparator={() => ReasonReact.null}
      renderItem={
        section =>
          <DocumentTileMasonryGrid
            data={section->SectionList.TitledSection.dataGet}
            readerPath
            columns=3
            gutter=42
          />
      }
      onEndReached=onPaginateDocuments
      endThreshold=2.0
      renderInnerContainer={
        children =>
          <div
            className={
              cn([
                "ph4",
                "pv5",
                "flex",
                "items-center",
                "flex-column",
                "bg-gray",
                "min-vh-100",
              ])
            }>
            <div> ...children </div>
          </div>
      }
    />,
};
