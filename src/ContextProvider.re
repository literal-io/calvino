let jssStyleID = "jss-server-side";

let tachyonsStyleSheet =
  Utils.requireJSS(
    "!../scripts/jss-loader!extract-loader!css-loader!tachyons/css/tachyons.css",
  )
  |> ReactJss.StyleSheet.make
  |> ReactJss.StyleSheet.attach;

let variablesStyleSheet =
  Utils.requireJSS("./static/variables.json")
  |> ReactJss.StyleSheet.make
  |> ReactJss.StyleSheet.attach;

let appStyleSheet =
  Utils.requireJSS(
    "!../scripts/jss-loader!extract-loader!css-loader!./static/app.css",
  )
  |> ReactJss.StyleSheet.make
  |> ReactJss.StyleSheet.attach;

[@bs.val] [@bs.module "@material-ui/core/styles"]
external createMuiTheme: Js.t({.}) => MaterialUi_Theme.Theme.t = "";

let defaultTheme = createMuiTheme(Js.Obj.empty());

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

module Client = {
  let component = ReasonReact.statelessComponent("ClientProvider");

  let make = (~generateClassName, ~theme=?, children) => {
    ...component,
    render: _self =>
      if (!Constants.canUseDOM) {
        ReasonReact.null;
      } else {
        let sheetsRegistry =
          Utils.(
            ReactJss.SheetsRegistry.make()
            *> ReactJss.SheetsRegistry.add(tachyonsStyleSheet)
            *> ReactJss.SheetsRegistry.add(variablesStyleSheet)
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

module Server = {
  let component = ReasonReact.statelessComponent("ServerProvider");

  let make =
      (~sheetsRegistry, ~generateClassName, ~theme, ~sheetsManager, children) => {
    ...component,
    render: _self =>
      if (Constants.canUseDOM) {
        ReasonReact.null;
      } else {
        let _ =
          Utils.(
            sheetsRegistry
            *> ReactJss.SheetsRegistry.add(tachyonsStyleSheet)
            *> ReactJss.SheetsRegistry.add(variablesStyleSheet)
            *> ReactJss.SheetsRegistry.add(appStyleSheet)
          );

        <ReactJss.JssProvider registry=sheetsRegistry generateClassName>
          <MaterialUi.MuiThemeProvider theme sheetsManager>
            children
          </MaterialUi.MuiThemeProvider>
        </ReactJss.JssProvider>;
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

  let make =
      (~sheetsRegistry, ~generateClassName, ~theme, ~sheetsManager, children) => {
    ...component,
    didMount: _self =>
      if (Constants.canUseDOM) {
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
      Constants.canUseDOM ?
        <Client generateClassName theme=defaultTheme> children </Client> :
        <Server
          sheetsRegistry generateClassName theme=defaultTheme sheetsManager>
          children
        </Server>,
  };
};

[@bs.deriving abstract]
type jsProps('a, 'b) = {
  generateClassName: ReactJss.GenerateClassName.t,
  theme: Js.t('a),
  sheetsRegistry: ReactJss.SheetsRegistry.t,
  sheetsManager: Js.t('b),
  children: ReasonReact.reactElement,
};

let default =
  ReasonReact.wrapReasonForJs(~component=Provider.component, jsProps =>
    Provider.make(
      ~generateClassName=jsProps->generateClassNameGet,
      ~sheetsRegistry=jsProps->sheetsRegistryGet,
      ~sheetsManager=jsProps->sheetsManagerGet,
      ~theme=`ObjectGeneric(jsProps->themeGet),
      jsProps->childrenGet,
    )
  );
