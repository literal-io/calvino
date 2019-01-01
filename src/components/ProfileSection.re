open Styles;
let component = ReasonReact.statelessComponent("ProfileSection");

let spacer = cn(["ma1"]);

module ActivityModel = {
  [@bs.deriving abstract]
  type t = {
    documentsCreated: int,
    highlightsCreated: int,
    pagesRead: int,
  };

  let make = t;

  let decode = json =>
    make(
      ~documentsCreated=json |> Json.Decode.(field("documentsCreated", int)),
      ~highlightsCreated=
        json |> Json.Decode.(field("highlightsCreated", int)),
      ~pagesRead=json |> Json.Decode.(field("pagesRead", int)),
    );
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
        {
          count
          |> Js.Option.map(Utils.wrapBs(string_of_int))
          |> Js.Option.getWithDefault("0")
          |> ReasonReact.string
        }
      </div>
      <div className={cn(["f7", "brand", "tl"])}>
        {ReasonReact.string(label)}
      </div>
    </div>
  </div>;

let renderActivity = (~activity, ()) =>
  <MaterialUi.Paper
    classes=[Root(cn(["bg-accent-100-o60", "pa3", "br1", "flex-auto"]))]>
    <div className={cn(["f7", "brand", "tl"])}>
      {ReasonReact.string("Recent Activity")}
    </div>
    <div
      style={make(~fontSize=rem(0.60), ())}
      className={cn(["f7", "brand-sl", "tl", "mb3"])}>
      {ReasonReact.string("Last 7 days")}
    </div>
    {
      renderActivityListItem(
        ~icon=<MaterialIcon.LibraryBooks />,
        ~count=
          activity
          |> Js.Option.map(Utils.wrapBs(ActivityModel.documentsCreatedGet)),
        ~label="Documents added",
        (),
      )
    }
    <div className={cn(["mv3"])} />
    {
      renderActivityListItem(
        ~icon=<MaterialIcon.Highlight />,
        ~count=
          activity
          |> Js.Option.map(Utils.wrapBs(ActivityModel.highlightsCreatedGet)),
        ~label="Highlights created",
        (),
      )
    }
    <div className={cn(["mv3"])} />
    {
      renderActivityListItem(
        ~icon=<MaterialIcon.Subject />,
        ~count=
          activity |> Js.Option.map(Utils.wrapBs(ActivityModel.pagesReadGet)),
        ~label="Pages read",
        (),
      )
    }
  </MaterialUi.Paper>;

let renderResumeReading = (~document, ~readerPath, ()) =>
  <AccentMonotoneButton
    className={cn(["flex-1", "flex", "items-stretch"])}
    href=?{
      document
      |> Js.Option.map(Utils.wrapBs(Utils.makeDocumentURL(~readerPath)))
    }
    contentClassName={cn(["flex", "flex-column", "flex-1", "pa3"])}>
    <div className={cn(["f7", "brand", "tl", "mb3"])}>
      {ReasonReact.string("Resume Reading")}
    </div>
    <div className={cn(["f5", "brand", "b", "i", "tl"])}>
      {
        document
        |> Js.Option.map((. document) =>
             document
             |> JavamonnBsLibrarian.DocumentModel.title
             |> (title => {j|$title,|j})
           )
        |> Js.Option.getWithDefault("")
        |> ReasonReact.string
      }
    </div>
    <div className={cn(["f5", "brand", "b", "i", "tl"])}>
      {
        document
        |> Js.Option.map(
             Utils.wrapBs(JavamonnBsLibrarian.DocumentModel.author),
           )
        |> Js.Option.getWithDefault("")
        |> ReasonReact.string
      }
    </div>
  </AccentMonotoneButton>;

let renderSettings = () =>
  <AccentMonotoneButton
    href="/account"
    className={cn(["flex-1", "flex", "items-stretch"])}
    contentClassName={
      cn(["flex", "flex-1", "items-center", "justify-center", "pa2"])
    }>
    <MaterialIcon.Settings style={bpl +++ square(28)} />
  </AccentMonotoneButton>;

let renderFeedback = () =>
  <AccentMonotoneButton
    className={cn(["flex-1", "flex", "items-stretch"])}
    href="mailto:hello@literal.io"
    contentClassName={
      cn(["flex", "flex-1", "items-center", "justify-center", "pa2"])
    }>
    <div className={cn(["flex", "flex-column", "justify-start"])}>
      <div className={cn(["f7", "brand", "tl"])}>
        {ReasonReact.string("Have feedback?")}
      </div>
    </div>
    <div className={cn(["mh2"])} />
    <MaterialIcon.MailOutline style={bpl +++ square(28)} />
  </AccentMonotoneButton>;

let make = (~readerPath, ~document, ~activity, _children) => {
  ...component,
  render: _self =>
    <div style={flex("1")} className={cn(["flex", "flex-row"])}>
      <div style={flex("1")} className={cn(["flex"])}>
        <div style={flex("1")} className={cn(["flex"])}>
          {renderActivity(~activity, ())}
        </div>
      </div>
      <div className=spacer />
      <div style={flex("1")} className={cn(["flex", "flex-column"])}>
        <div style={flex("7")} className={cn(["flex"])}>
          {renderResumeReading(~document, ~readerPath, ())}
        </div>
        <div className=spacer />
        <div style={flex("3")} className={cn(["flex", "flex-row"])}>
          <div style={flex("3")} className={cn(["flex"])}>
            {renderSettings()}
          </div>
          <div className=spacer />
          <div style={flex("6")} className={cn(["flex"])}>
            {renderFeedback()}
          </div>
        </div>
      </div>
    </div>,
};
