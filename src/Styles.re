let (+++) = ReactDOMRe.Style.combine;
let make = ReactDOMRe.Style.make;
let px = num => string_of_int(num) ++ "px";
let rem = num => string_of_float(num) ++ "rem";
let vh = num => string_of_int(num) ++ "vh";
let cn = Cn.make;

module Color = {
  let brandColor = "#546E7A";
  let accentColor = "rgb(0, 188, 212)";
  let primaryLight = "rgba(255, 255, 255, 0.92)";
  let secondaryLight = "rgba(255, 255, 255, 0.72)";
  let dividerLight = "rgba(255, 255, 255, 0.12)";
};

let bgWhite = make(~backgroundColor="white", ());

let pl = make(~color=Color.primaryLight, ());
let sl = make(~color=Color.secondaryLight, ());

let bpl = make(~color=Color.brandColor, ());
let bsl = make(~color=Color.brandColor, ~opacity=string_of_float(0.72), ());

let f_pl = make(~fill=Color.primaryLight, ());

let fillBrandA = alpha => make(~fill={j|rgba(84, 110, 122, $alpha)|j}, ());
let brandA = alpha => make(~color={j|rgba(84, 110, 122, $alpha)|j}, ());
let bga = alpha =>
  make(~backgroundColor={j|rgba(84, 110, 122, $alpha)|j}, ());
let bgaAccent = alpha =>
  make(~backgroundColor={j|rgba(0, 188, 212, $alpha)|j}, ());

let lineHeight = lh => make(~lineHeight=lh, ());
let square = size => make(~width=px(size), ~height=px(size), ());
let flex = v => make(~flex=v, ());
let maxWidth = mw => make(~maxWidth=mw, ());
