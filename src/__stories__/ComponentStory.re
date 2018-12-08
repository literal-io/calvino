open BsStorybook.Story;
open Styles;
open StoryUtils;

let _module = [%bs.raw "module"];
let highlightText = "Contemplating these essential landscapes, Kublai reflected on the invisible order that sustains cities, on the rules that decreed how they rise, take shape and prosper, adapting themselves to the seasons, and then how they sadden and fall in ruins.";

storiesOf("Components", _module)
->(
    add("MaterialIcon", () =>
      <AppFrame>
        <MaterialIcon.CloudOutline style={pl +++ square(36)} />
      </AppFrame>
    )
  )
->(
    add("IconListItem", () =>
      <AppFrame>
        <IconListItem
          icon={
            <div className={cn(["pl"])}>
              <MaterialIcon.CloudOutline style={pl +++ square(36)} />
            </div>
          }
          title="Cloud Connected"
          description="Connect Literal to your Google Drive and Dropbox"
          titleClassName={cn(["f7", "pl", "b", "mb1"])}
          descriptionClassName={cn(["f7", "sl"])}
        />
      </AppFrame>
    )
  )
->(
    add("RegistrationIconList", () =>
      <AppFrame>
        <RegistrationIconList
          className={cn(["pa3_5", "pv3"])}
          iconClassName={cn(["pl", "sq36"])}
          iconStyle={pl +++ square(36)}
          titleClassName={cn(["f7", "pl", "b", "mb1"])}
          descriptionClassName={cn(["f7", "sl"])}
          renderSeparator={() => <div className={cn(["mb3"])} />}
        />
      </AppFrame>
    )
  )
->(add("RegistrationCTA", () => <AppFrame> <RegistrationCTA /> </AppFrame>))
->(
    add("AccentMonotoneButton", () =>
      <AppFrame>
        <AccentMonotoneButton
          onClick={() => ()}
          className={
            cn(["flex", "flex-row", "justify-center", "items-center", "pa2"])
          }>
          <MaterialIcon.MailOutline style=bpl />
          <div className={cn(["mh2"])} />
          <div className={cn(["flex", "flex-column", "justify-start"])}>
            <div className={cn(["f7", "brand", "tl"])}>
              {ReasonReact.string("Have feedback?")}
            </div>
            <div className={cn(["f7", "brand", "tl"])}>
              {ReasonReact.string("Send us your thoughts.")}
            </div>
          </div>
        </AccentMonotoneButton>
      </AppFrame>
    )
  )
->(
    add("ProfileSection", () =>
      <AppFrame>
        <div
          className={cn(["flex"])}
          style={flex("1") +++ make(~width=px(450), ~height=px(250), ())}>
          <ProfileSection
            onSettingsClicked={() => ()}
            onFeedbackClicked={() => ()}
            onResumeReadingClicked={() => ()}
            activity=ProfileSection.{
              documentsCreated: Js.Math.random_int(8, 40),
              highlightsCreated: Js.Math.random_int(8, 4),
              pagesRead: Js.Math.random_int(20, 120),
            }
            document={Mocks.document()}
          />
        </div>
      </AppFrame>
    )
  );

storiesOf("Components/DocumentAnnotationTile", _module)
->(
    add("Unconstrained", () =>
      <AppFrame>
        <DocumentAnnotationTile
          title="Invisible Cities"
          author="Italo Calvino"
          annotationURL="http://localhost:5900"
          text=highlightText
          onShareClicked={() => ()}
        />
      </AppFrame>
    )
  )
->(
    add("Constrained Width", () =>
      <AppFrame>
        <div style={make(~width=px(350), ())}>
          <DocumentAnnotationTile
            title="Invisible Cities"
            annotationURL="http://localhost:5900"
            author="Italo Calvino"
            text=highlightText
            onShareClicked={() => ()}
          />
        </div>
      </AppFrame>
    )
  );

storiesOf("Components/DocumentTile", _module)
->(
    add("With Unprocessed Image", () =>
      <AppFrame>
        <DocumentTile
          title="Invisible Cities"
          author="Italo Calvino"
          imageURL="https://storage.googleapis.com/literal-images/000da7f0-6254-11e8-b634-240dbf38c455"
          documentURL="http://localhost:9001"
        />
      </AppFrame>
    )
  )
->(
    add("With Processed Image", () =>
      <AppFrame>
        <DocumentTile
          title="Invisible Cities"
          author="Italo Calvino"
          imageURL="https://storage.googleapis.com/literal-images/000d0c10-d07b-11e8-9dfc-91637d54bf9b"
          documentURL="http://localhost:9001"
        />
      </AppFrame>
    )
  )
->(
    add("Without Image", () =>
      <AppFrame>
        <DocumentTile
          title="Invisible Cities"
          author="Italo Calvino"
          documentURL="http://localhost:9001"
        />
      </AppFrame>
    )
  );
