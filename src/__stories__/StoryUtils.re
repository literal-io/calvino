module AppFrame = {
  let component = ReasonReact.statelessComponent("AppFrame");

  let make = children => {
    ...component,
    render: _self =>
      <ContextProvider.Client
        generateClassName={ReactJss.GenerateClassName.make()}>
        <div className={Styles.cn(["ff-r", "bg-brand", "pa4"])}> ...children </div>
      </ContextProvider.Client>,
  };
};
