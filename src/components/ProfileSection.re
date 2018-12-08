open Styles;
let component = ReasonReact.statelessComponent("ProfileSection");

let spacer = cn(["ma1"]);

type activity = {
  documentsCreated: int,
  highlightsCreated: int,
  pagesRead: int,
};

let renderActivityListItem = (~icon, ~count, ~label, ()) =>
  <div className={cn(["flex", "flex-row", "items-center"])}>
    {
      ReasonReact.cloneElement(
        icon,
        ~props={"style": bpl +++ square(26)},
        [||],
      )
    }
    <div className={cn(["mh2"])} />
    <div className={cn(["flex", "flex-column"])}>
      <div className={cn(["f5", "b", "brand", "tl"])}>
        {count |> string_of_int |> ReasonReact.string}
      </div>
      <div className={cn(["f7", "brand", "tl"])}>
        {ReasonReact.string(label)}
      </div>
    </div>
  </div>;

let renderActivity = (~activity, ()) =>
  <MaterialUi.Paper classes=[Root(cn(["bg-accent-100-o60", "pa3", "br1"]))]>
    <div className={cn(["f7", "brand", "tl", "mb3"])}>
      {ReasonReact.string("Activity This Week")}
    </div>
    {
      renderActivityListItem(
        ~icon=<MaterialIcon.LibraryBooks />,
        ~count=activity.documentsCreated,
        ~label="Documents added",
        (),
      )
    }
    <div className={cn(["mv3"])} />
    {
      renderActivityListItem(
        ~icon=<MaterialIcon.Highlight />,
        ~count=activity.highlightsCreated,
        ~label="Highlights created",
        (),
      )
    }
    <div className={cn(["mv3"])} />
    {
      renderActivityListItem(
        ~icon=<MaterialIcon.Subject />,
        ~count=activity.pagesRead,
        ~label="Pages read",
        (),
      )
    }
  </MaterialUi.Paper>;

let renderResumeReading = (~document, ~onResumeReadingClicked, ()) =>
  <AccentMonotoneButton
    onClick={() => onResumeReadingClicked()}
    className={cn(["flex-auto"])}
    contentClassName={
      cn(["absolute--fill", "absolute", "flex", "flex-column", "pa3"])
    }>
    <div className={cn(["f7", "brand", "tl", "mb3"])}>
      {ReasonReact.string("Resume Reading")}
    </div>
    <div className={cn(["f5", "brand", "b", "i", "tl"])}>
      {
        document
        |> JavamonnBsLibrarian.DocumentModel.title
        |> (title => {j|$title,|j})
        |> ReasonReact.string
      }
    </div>
    <div className={cn(["f5", "brand", "b", "i", "tl"])}>
      {
        document
        |> JavamonnBsLibrarian.DocumentModel.author
        |> ReasonReact.string
      }
    </div>
  </AccentMonotoneButton>;

let renderSettings = (~onSettingsClicked, ()) =>
  <AccentMonotoneButton
    onClick={() => onSettingsClicked()}
    className={cn(["flex-auto"])}
    contentClassName={
      cn([
        "absolute--fill",
        "absolute",
        "flex",
        "items-center",
        "justify-center",
      ])
    }>
    <MaterialIcon.Settings style={bpl +++ square(28)} />
  </AccentMonotoneButton>;

let renderFeedback = (~onFeedbackClicked, ()) =>
  <AccentMonotoneButton
    onClick={() => onFeedbackClicked()}
    className={cn(["flex-auto"])}
    contentClassName={
      cn([
        "absolute--fill",
        "absolute",
        "flex",
        "items-center",
        "justify-center",
        "pa2",
      ])
    }>
    <div className={cn(["flex", "flex-column", "justify-start"])}>
      <div className={cn(["f7", "brand", "tl"])}>
        {ReasonReact.string("Have feedback?")}
      </div>
    </div>
    <div className={cn(["mh2"])} />
    <MaterialIcon.MailOutline style={bpl +++ square(28)} />
  </AccentMonotoneButton>;

let make =
    (
      ~onSettingsClicked,
      ~onFeedbackClicked,
      ~onResumeReadingClicked,
      ~document,
      ~activity,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div style={flex("1")} className={cn(["flex", "flex-row"])}>
      <div style={flex("1")} className={cn(["flex"])}>
        <div style={flex("1")}> {renderActivity(~activity, ())} </div>
      </div>
      <div className=spacer />
      <div style={flex("1")} className={cn(["flex", "flex-column"])}>
        <div style={flex("7")} className={cn(["flex"])}>
          {renderResumeReading(~document, ~onResumeReadingClicked, ())}
        </div>
        <div className=spacer />
        <div style={flex("3")} className={cn(["flex", "flex-row"])}>
          <div style={flex("3")} className={cn(["flex"])}>
            {renderSettings(~onSettingsClicked, ())}
          </div>
          <div className=spacer />
          <div style={flex("6")} className={cn(["flex"])}>
            {renderFeedback(~onFeedbackClicked, ())}
          </div>
        </div>
      </div>
    </div>,
};
