open Styles;

let component = ReasonReact.statelessComponent("DocumentDetail");

let make =
    (
      ~userDocument,
      ~document,
      ~onMinimize,
      ~onBack,
      ~onDocumentShare,
      ~onDocumentSave,
      ~onDocumentDelete,
      ~onTitleChange,
      ~onAuthorChange,
      ~firstDocumentOpenActivity,
      ~lastDocumentOpenActivity,
      ~documentAnnotations,
      ~onPaginateDocumentAnnotations,
      ~onDocumentAnnotationTileClick,
      ~onDocumentAnnotationTileShare,
      ~userProfileId,
      ~readerPath,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div
      className={cn(["flex", "flex-column", "flex-auto", "ff-r", "shadow"])}>
      <div className={cn(["bg-brand", "z-2"])}>
        <DocumentDetailNavBar onBack onMinimize />
        <Spacer size=4 />
        <div className={cn(["ph4"])}>
          <DocumentDetailHeader
            title={
              userDocument
              |> Js.Option.map(
                   Utils.wrapBs(JavamonnBsLibrarian.UserDocumentModel.title),
                 )
            }
            author={
              userDocument
              |> Js.Option.map(
                   Utils.wrapBs(JavamonnBsLibrarian.UserDocumentModel.author),
                 )
            }
            onTitleChange
            onAuthorChange
          />
        </div>
        <Spacer size=4 />
        <div className={cn(["ph4"])}>
          <DocumentDetailActionButtons
            onShare=onDocumentShare
            onSave=onDocumentSave
            onDelete=onDocumentDelete
            onGetDocumentShareClipboardText={() =>
              document
              |> Js.Option.map(
                   Utils.wrapBs(Utils.makeDocumentURL(~readerPath)),
                 )
              |> Js.Option.getWithDefault("")
            }
          />
        </div>
        <Spacer size=4 />
      </div>
      <DocumentDetailTabs
        document
        firstDocumentOpenActivity
        lastDocumentOpenActivity
        documentAnnotations
        onPaginateDocumentAnnotations
        onDocumentAnnotationTileClick
        onDocumentAnnotationTileShare
        userProfileId
        readerPath
      />
    </div>,
};
