open BsStorybook.Story;
open Styles;

let _module = [%bs.raw "module"];

module AppFrame = {
  let component = ReasonReact.statelessComponent("AppFrame");

  let make = children => {
    ...component,
    render: _self =>
      <div className={cn(["ff-r", "bg-brand", "pa4"])}> ...children </div>,
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
