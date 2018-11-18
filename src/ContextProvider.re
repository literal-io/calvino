let jssStyleID = "jss-server-side";

module Window = {
  type t;

  [@bs.val] external window: Js.Nullable.t(t) = "";

  /* let exists = window |> Js.Nullable.toOption |> Js.Option.isSome; */

  let exists = false;
};

let tachyonsStyleSheet =
  Utils.requireJSS("tachyons/css/tachyons.css")
  |> ReactJss.StyleSheet.make
  |> ReactJss.StyleSheet.attach;

let appStyleSheet =
  Utils.requireJSS("./static/app.css")
  |> ReactJss.StyleSheet.make
  |> ReactJss.StyleSheet.attach;

module Client = {
  let component = ReasonReact.statelessComponent("ClientProvider");

  let make = (~generateClassName, ~theme=?, children) => {
    ...component,
    render: _self => {
      let sheetsRegistry =
        Utils.(
          ReactJss.SheetsRegistry.make()
          *> ReactJss.SheetsRegistry.add(tachyonsStyleSheet)
          *> ReactJss.SheetsRegistry.add(appStyleSheet)
        );
      switch (theme) {
      | Some(theme) =>
        <ReactJss.JssProvider generateClassName registry=sheetsRegistry>
          <MaterialUi.MuiThemeProvider theme>
            children
          </MaterialUi.MuiThemeProvider>
        </ReactJss.JssProvider>
      | None =>
        <ReactJss.JssProvider generateClassName registry=sheetsRegistry>
          ...children
        </ReactJss.JssProvider>
      };
    },
  };
};

/**
 * Currently we assume that Calvino screens are the only material-ui components in the Render
 * tree, and wrap directly with the required component (JssProvider, MuiThemeProvider). In
 * the future, one should be able to opt out of this in favor of material-ui Providers at the
 * root level.
 */
module Provider = {
  let component = ReasonReact.statelessComponent("Provider");

  let renderServerSide =
      (~sheetsRegistry, ~generateClassName, ~theme, ~sheetsManager, children) => {
    let _ =
      Utils.(
        sheetsRegistry
        *> ReactJss.SheetsRegistry.add(tachyonsStyleSheet)
        *> ReactJss.SheetsRegistry.add(appStyleSheet)
      );

    <ReactJss.JssProvider registry=sheetsRegistry generateClassName>
      <MaterialUi.MuiThemeProvider theme sheetsManager>
        children
      </MaterialUi.MuiThemeProvider>
    </ReactJss.JssProvider>;
  };

  let renderClientSide = (~generateClassName, ~theme, children) => {
    let sheetsRegistry =
      Utils.(
        ReactJss.SheetsRegistry.make()
        *> ReactJss.SheetsRegistry.add(tachyonsStyleSheet)
        *> ReactJss.SheetsRegistry.add(appStyleSheet)
      );

    <ReactJss.JssProvider generateClassName registry=sheetsRegistry>
      <MaterialUi.MuiThemeProvider theme>
        children
      </MaterialUi.MuiThemeProvider>
    </ReactJss.JssProvider>;
  };

  let make =
      (~sheetsRegistry, ~generateClassName, ~theme, ~sheetsManager, children) => {
    ...component,
    didMount: _self =>
      if (Window.exists) {
        let _ =
          Webapi.Dom.(
            document
            |> Document.getElementById(jssStyleID)
            |> Js.Option.andThen((. node) =>
                 node
                 |> Element.parentNode
                 |> Js.Option.map((. parent) =>
                      Node.removeChild(node, parent)
                    )
               )
          );
        ();
      },
    render: _self =>
      Window.exists ?
        <Client generateClassName theme> children </Client> :
        renderServerSide(
          ~sheetsRegistry,
          ~generateClassName,
          ~theme,
          ~sheetsManager,
          children,
        ),
  };
};

/**
 * On the client, we only need a subset of context values. This function is called through
 * by JS as part of client-side app initialization and passed through to Provider.
 */
let makeClientContext = theme => {
  "generateClassName": ReactJss.GenerateClassName.make(),
  "theme": theme,
};

let makeServerContext = theme => {
  "generateClassName": ReactJss.GenerateClassName.make(),
  "sheetsRegistry": ReactJss.SheetsRegistry.make(),
  "sheetsManager": ReactJss.SheetsManager.make(),
  "jssStyleID": jssStyleID,
  "theme": theme,
};
