[@bs.val] external requireJSS: string => Js.Json.t = "require";

/* doto operator, used to chain unit returning methods */
let ( *> ) = (x, f) => {
  let _ = f(x);
  x;
};
