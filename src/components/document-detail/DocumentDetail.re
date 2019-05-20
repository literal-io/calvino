open Styles;

let component = ReasonReact.statelessComponent("DocumentDetail");

let make = (~document, ~onMinimize, ~onBack, _children) => {
  ...component, 
  render: _self =>
    <div className={cn(["flex", "flex-column", "flex-auto", "ff-r"])}>
      <DocumentDetailNavBar
        onBack={onBack}
        onMinimize={onMinimize}
      />
    </div>
}
