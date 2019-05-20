open Styles;

let component = ReasonReact.statelessComponent("DocumentDetailNavBar");

let make = (~onBack, ~onMinimize, _children) => {
  ...component,
  render: _self =>
    <div
      style={make(
        ~height=px(48),
        ~borderColor={
          Color.dividerLight;
        },
        (),
      )}
      className={cn(["flex", "bb", "flex-row", "justify-between"])}>
      <MaterialUi.IconButton onClick={_ev => onBack()}>
        <MaterialIcon.ArrowBack style={square(24) +++ pl} />
      </MaterialUi.IconButton>
      <MaterialUi.IconButton onClick={_ev => onMinimize()}>
        <MaterialIcon.ChromeReaderMode style={square(24) +++ pl} />
      </MaterialUi.IconButton>
    </div>,
};
