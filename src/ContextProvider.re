let jssStyleID = "jss-server-side";

module Window = {
  type t;

  [@bs.val] external window: Js.Nullable.t(t) = "";

  /* let exists = window |> Js.Nullable.toOption |> Js.Option.isSome; */

  let exists = false;
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
      (~sheetsRegistry, ~generateClassName, ~theme, ~sheetsManager, children) =>
    <ReactJss.JssProvider registry=sheetsRegistry generateClassName>
      <MaterialUi.MuiThemeProvider theme sheetsManager>
        children
      </MaterialUi.MuiThemeProvider>
    </ReactJss.JssProvider>;

  let renderClientSide = (~generateClassName, ~theme, children) =>
    <ReactJss.JssProvider generateClassName>
      <MaterialUi.MuiThemeProvider theme>
        children
      </MaterialUi.MuiThemeProvider>
    </ReactJss.JssProvider>;

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
        renderClientSide(~generateClassName, ~theme, children) :
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
let makeClientContext = (theme) => {
  "generateClassName": ReactJss.GenerateClassName.make(),
  "theme": theme
};

let makeServerContext = (theme) => {
  "generateClassName": ReactJss.GenerateClassName.make(),
  "sheetsRegistry": ReactJss.SheetsRegistry.make(),
  "sheetsManager": ReactJss.SheetsManager.make(),
  "jssStyleID": jssStyleID,
  "theme": theme
};

