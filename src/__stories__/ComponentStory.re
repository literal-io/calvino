open BsStorybook.Story;
open Styles;

let _module = [%bs.raw "module"];

module AppFrame = {
  let component = ReasonReact.statelessComponent("AppFrame");

  let make = children => {
    ...component,
    render: _self =>
      <ContextProvider.Client
        generateClassName={ReactJss.GenerateClassName.make()}>
        <div className={cn(["ff-r", "bg-brand", "pa4"])}> ...children </div>
      </ContextProvider.Client>,
  };
};

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
->(add("RegistrationCTA", () => <AppFrame> <RegistrationCTA /> </AppFrame>));

let highlightText = "Contemplating these essential landscapes, Kublai reflected on the invisible order that sustains cities, on the rules that decreed how they rise, take shape and prosper, adapting themselves to the seasons, and then how they sadden and fall in ruins.";
storiesOf("Components/HighlightListItem", _module)
->(
    add("Unconstrained", () =>
      <AppFrame>
        <HighlightListItem
          title="Invisible Cities"
          author="Italo Calvino"
          text=highlightText
        />
      </AppFrame>
    )
  )
->(
    add("Constrained Width", () =>
      <AppFrame>
        <div style={make(~width=px(350), ())}>
          <HighlightListItem
            title="Invisible Cities"
            author="Italo Calvino"
            text=highlightText
          />
        </div>
      </AppFrame>
    )
  );
