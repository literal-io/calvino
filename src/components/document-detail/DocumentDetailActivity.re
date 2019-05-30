open Styles;

let component = ReasonReact.statelessComponent("DocumentDetailActivity");

let activityItem = (~icon, ~label, ~value) =>
  <div className={cn(["flex", "flex-row", "pa3"])}>
    icon
    <Spacer size=2 />
    <div className={cn(["flex", "flex-column"])}>
      <span className={cn(["sl", "mb1"])}>
        {ReasonReact.string(label)}
      </span>
      <span className={cn(["pl"])}> {ReasonReact.string(value)} </span>
    </div>
  </div>;

let make =
    (
      ~firstDocumentOpenActivity,
      ~lastDocumentOpenActivity,
      ~document,
      _children,
    ) => {
  ...component,
  render: self => {
    let source =
      switch (
        document
        |> JavamonnBsLibrarian.DocumentModel.originSource
        |> Js.Option.map(
             Utils.wrapBs(
               JavamonnBsLibrarian.DocumentModel.OriginSource.type_,
             ),
           )
      ) {
      | Some(`Web) =>
        document
        |> JavamonnBsLibrarian.DocumentModel.originSource
        |> Js.Option.andThen(
             Utils.wrapBs(JavamonnBsLibrarian.DocumentModel.OriginSource.url),
           )
        |> Js.Option.map((. url) =>
             url |> Webapi.Url.make |> Webapi.Url.host
           )
        |> Js.Option.getWithDefault("Web")
      | Some(`GoogleDrive) => "Google Drive"
      | Some(`Dropbox) => "Dropbox"
      | None => "Unknown"
      };
    let firstOpened =
      firstDocumentOpenActivity
      |> JavamonnBsLibrarian.UserReadActivityModel.createdAt
      |> DateFns.parseString
      |> DateFns.format("DD MMM YYYY");
    let lastOpened =
      lastDocumentOpenActivity
      |> JavamonnBsLibrarian.UserReadActivityModel.createdAt
      |> DateFns.parseString
      |> DateFns.format("DD MMM YYYY");
    <div
      className={cn([
        "flex",
        "bg-gray",
        "ph3",
        "pt4",
        "flex-auto",
        "absolute",
        "absolute--fill",
        "flex-column",
      ])}>
      <span className={cn(["ml3", "sd", "f6", "b", "mb3"])}>
        {ReasonReact.string("History")}
      </span>
      <MaterialUi.Paper classes=[Root("bg-brand")]>
        {activityItem(
           ~icon=<MaterialIcon.Web style={square(36) +++ sl} />,
           ~label="Source",
           ~value=source,
         )}
        {activityItem(
           ~icon=<MaterialIcon.PanoramaFishEye style={square(36) +++ sl} />,
           ~label="First Opened",
           ~value=firstOpened,
         )}
        {activityItem(
           ~icon=<MaterialIcon.Timelapse style={square(36) +++ sl} />,
           ~label="Last Opened",
           ~value=lastOpened,
         )}
      </MaterialUi.Paper>
    </div>;
  },
};
