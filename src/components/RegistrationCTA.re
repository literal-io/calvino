open Styles;

let component = ReasonReact.statelessComponent("RegistrationCTA");

let make = _children => {
  ...component,
  render: _self =>
    <div
      className={
        cn([
          "flex",
          "flex-auto",
          "flex-row",
          "justify-center",
          "items-center",
          "bg-accent-100-o60",
          "pv3"
        ])
      }>
      <div className={cn(["flex", "flex-column"])}>
        <div className={cn(["flex", "flex-column"])}>
          <span className={cn(["b", "f2", "bpl", "mb1"])}>
            {ReasonReact.string("Literal.")}
          </span>
          <span className={cn(["fw5", "f3", "bpl"])}>
            {ReasonReact.string("A PDF Reader built for the web.")}
          </span>
        </div>
        <RegistrationIconList
          className={cn(["mv5"])}
          iconClassName={cn(["bpl"])}
          iconStyle={bpl +++ square(42)}
          titleClassName={cn(["bpl", "b", "mb2", "f5"])}
          descriptionClassName={cn(["bsl", "sl", "f5"])}
          renderSeparator={() => <div className={cn(["mb4"])} />}
        />
        <span className={cn(["fw5", "f3", "bpl"])}>
          {ReasonReact.string("Create a free account to get started.")}
        </span>
      </div>
    </div>,
};
