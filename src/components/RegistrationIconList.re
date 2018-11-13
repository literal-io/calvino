open Styles;

type featureSection = {
  icon: ReasonReact.reactElement,
  title: string,
  description: string,
};

let component = ReasonReact.statelessComponent("RegistrationIconList");

let make =
    (
      ~className,
      ~iconClassName,
      ~titleClassName,
      ~descriptionClassName,
      ~renderSeparator,
      ~iconStyle,
      _children,
    ) => {
  ...component,
  render: _self => {
    let sections = [|
      {
        icon: <MaterialIcon.LibraryBooks style=iconStyle />,
        title: "Digital Librarian",
        description: "Automatically archive PDFs you open",
      },
      {
        icon: <MaterialIcon.Highlight style=iconStyle />,
        title: "Highlights",
        description: "Save and share your favorite pieces of text",
      },
      {
        icon: <MaterialIcon.CloudOutline style=iconStyle />,
        title: "Cloud Connected",
        description: "Connect Literal to your Google Drive and Dropbox",
      },
      {
        icon: <MaterialIcon.TextFields style=iconStyle />,
        title: "Optical Character Recognition",
        description: "Make scanned documents searchable",
      },
    |];

    <div className={cn([className, "flex", "flex-column"])}>
      ...{
           sections
           |> Array.mapi((idx, {icon, title, description}) =>
                <>
                  <IconListItem
                    icon={<div className=iconClassName> icon </div>}
                    titleClassName
                    descriptionClassName
                    title
                    description
                  />
                  {
                    idx < Array.length(sections) - 1 ?
                      renderSeparator() : ReasonReact.null
                  }
                </>
              )
         }
    </div>;
  },
};
