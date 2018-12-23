open Styles;

type feature = {
  title: string,
  icon: ReasonReact.reactElement,
  description: string,
};

let features = [|
  {
    icon: <MaterialIcon.ChromeReaderMode style={square(46) +++ sl} />,
    title: "Designed for Reading",
    description: "Upgrades your browser's default PDF reader",
  },
  {
    icon: <MaterialIcon.LibraryBooks style={square(46) +++ sl} />,
    title: "Library Management",
    description: "Never lose a document and access from anywhere",
  },
  {
    icon: <MaterialIcon.CloudOutline style={square(46) +++ sl} />,
    title: "Cloud Connected",
    description: "Integrates with Google Drive and Dropbox",
  },
  {
    icon: <MaterialIcon.Highlight style={square(46) +++ sl} />,
    title: "Highlights",
    description: "Save and share your favorite pieces of text",
  },
  {
    icon: <MaterialIcon.TextFields style={square(46) +++ sl} />,
    title: "Optical Character Recognition",
    description: "Automatically apply text layer to make scanned documents searchable",
  },
  {
    icon: <MaterialIcon.BarChart style={square(46) +++ sl} />,
    title: "Reading Analytics",
    description: "Motivate yourself with reading activity analytics and automatically resume progress",
  },
|];

let renderFeatureColumn = features =>
  <div
    style={make(~maxWidth=px(500), ())}
    className={cn(["flex", "flex-column", "justify-between", "flex-auto"])}>
    ...{
         features
         |> Array.mapi((idx, {icon, title, description}) =>
              <IconListItem
                className={idx < Array.length(features) - 1 ? "mb4" : ""}
                icon={<div className={cn(["mr2"])}> icon </div>}
                title
                description
                titleClassName={cn(["pl", "b", "f4", "mb2"])}
                descriptionClassName={cn(["sl", "f5"])}
              />
            )
       }
  </div>;

let component = ReasonReact.statelessComponent("LandingFeatureSection");
let make = _children => {
  ...component,
  render: _self =>
    <div
      className={
        cn([
          "bg-brand",
          "pa5",
          "flex",
          "flex-row",
          "justify-center",
          "items-stretch",
        ])
      }>
      {features |> Js.Array.slice(~start=0, ~end_=3) |> renderFeatureColumn}
      <Spacer size=5 />
      {features |> Js.Array.sliceFrom(3) |> renderFeatureColumn}
    </div>,
};
