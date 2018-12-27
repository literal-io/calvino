let component = ReasonReact.statelessComponent("AnalyticsButton");

let inst =
  GAnalytics.make(Constants.googleAnalyticsTrackerId, Js.Nullable.null, true);

let make =
    (
      ~href=?,
      ~style=?,
      ~classes=?,
      ~variant=?,
      ~eventType,
      ~eventOptions,
      children,
    ) => {
  let handleClick = _ev => {
    if (Constants.isDevelopment) {
      Js.log3("AnalyticsButton event:", eventType, eventOptions);
    } else {
      let _ = GAnalytics.send(eventType, eventOptions);
      ();
    };
    let _ =
      switch (href) {
      | Some(href) =>
        Webapi.Dom.((window |> Window.location)->(Location.setHref(href)))
      | None => ()
      };
    ();
  };

  {
    ...component,
    render: _self =>
      <MaterialUi.Button ?style ?classes ?variant onClick=handleClick>
        children
      </MaterialUi.Button>,
  };
};
