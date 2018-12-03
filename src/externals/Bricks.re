type t;

module Params = {
  [@bs.deriving abstract]
  type size = {
    columns: int,
    gutter: int,
    [@bs.optional]
    mq: string,
  };

  [@bs.deriving abstract]
  type t = {
    container: Dom.element,
    packed: string,
    sizes: array(size),
  };

  let makeSize = size;
  let make = t;
};

[@bs.val] [@bs.module "bricks.js"] external make: Params.t => t = "default";

[@bs.send] external pack: t => t = "";
[@bs.send] external update: t => t = "";
