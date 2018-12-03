[@bs.val] [@bs.module "lodash-es/debounce"]
external debounce: ((. 'a) => 'b, int) => (. 'a) => 'b = "default";

[@bs.val] [@bs.module "lodash-es/throttle"]
external throttle: ((. 'a) => 'b, int) => (. 'a) => 'b = "default";
