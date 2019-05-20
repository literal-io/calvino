module AppFrame = {
  let component = ReasonReact.statelessComponent("AppFrame");

  let make = (~style=?, children) => {
    ...component,
    render: _self =>
      <ContextProvider.Client
        generateClassName={ReactJss.GenerateClassName.make()}>
        <div className={Styles.cn(["ff-r", "bg-brand", "pa4"])} ?style>
          ...children
        </div>
      </ContextProvider.Client>,
  };
};
