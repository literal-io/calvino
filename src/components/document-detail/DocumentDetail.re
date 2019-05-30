open Styles;

let component = ReasonReact.statelessComponent("DocumentDetail");

let make =
    (
      ~document,
      ~onMinimize,
      ~onBack,
      ~onDocumentShare,
      ~onDocumentSave,
      ~onDocumentDelete,
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
    <div className={cn(["flex", "flex-column", "flex-auto", "ff-r"])}>
      <DocumentDetailNavBar onBack onMinimize />
      <Spacer size=3 />
      <div className={cn(["ph4"])}>
        <DocumentDetailHeader
          title={JavamonnBsLibrarian.DocumentModel.title(document)}
          author={JavamonnBsLibrarian.DocumentModel.author(document)}
        />
      </div>
      <Spacer size=3 />
      <div className={cn(["ph4"])}>
        <DocumentDetailActionButtons
          onShare=onDocumentShare
          onSave=onDocumentSave
          onDelete=onDocumentDelete
        />
      </div>
      <Spacer size=3 />
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
