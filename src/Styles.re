let (+++) = ReactDOMRe.Style.combine;
let make = ReactDOMRe.Style.make;
let px = num => string_of_int(num) ++ "px";
let cn = Cn.make;

let getCSSVariable: string => string = [%raw
  "function getCSSVariable(cssVar) { return getComputedStyle(document.body).getPropertyValue(cssVar) }"
];

module Color = {
  let brandColor = getCSSVariable("--brand-color");
  let accentColor = getCSSVariable("--accent-color");
  let primaryLight = getCSSVariable("--primary-light");
};

let bgWhite = make(~backgroundColor="white", ());
let pl = make(~color=Color.primaryLight, ());
let bpl = make(~color=Color.brandColor, ());
let f_pl = make(~fill=Color.primaryLight, ());
let square = size => make(~width=px(size), ~height=px(size), ());
