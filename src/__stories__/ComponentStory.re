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
->(add("MaterialIcon", () => 
    <AppFrame>
      <MaterialIcon.CloudOutline style={pl +++ square(36)} />
    </AppFrame>
  ))
->(
    add("IconListItem", () =>
      <AppFrame>
        <IconListItem
          icon={<MaterialIcon.CloudOutline style={pl +++ square(36)} />}
          title="Cloud Connected"
          description="Connect Literal to your Google Drive and Dropbox"
        />
      </AppFrame>
    )
  );
