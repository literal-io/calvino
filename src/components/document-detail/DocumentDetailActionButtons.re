open Styles;

let component = ReasonReact.statelessComponent("DocumentDetailActionButtons");

let buttonStyle =
  make(
    ~borderRadius="50%",
    ~border="solid 1px rgba(255, 255, 255, 0.32)",
    (),
  );

let make = (~onShare, ~onSave, ~onDelete, _children) => {
  ...component,
  render: _self =>
    <div className={cn(["flex", "flex-row"])}>
      <MaterialUi.IconButton style=buttonStyle onClick={_ev => onShare()}>
        <MaterialIcon.Share style={square(24) +++ sl} />
      </MaterialUi.IconButton>
      <Spacer size=2 />
      <MaterialUi.IconButton style=buttonStyle onClick={_ev => onSave()}>
        <MaterialIcon.Download style={square(24) +++ sl} />
      </MaterialUi.IconButton>
      <Spacer size=2 />
      <MaterialUi.IconButton style=buttonStyle onClick={_ev => onDelete()}>
        <MaterialIcon.Delete style={square(24) +++ sl} />
      </MaterialUi.IconButton>
    </div>,
};
