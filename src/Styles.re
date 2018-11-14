let (+++) = ReactDOMRe.Style.combine;
let make = ReactDOMRe.Style.make;
let px = num => string_of_int(num) ++ "px";
let cn = Cn.make;

module Color = {
  let brandColor = "#546E7A";
  let accentColor = "rgb(0, 188, 212)";
  let primaryLight = "rgba(255, 255, 255, 0.92)";
};

let bgWhite = make(~backgroundColor="white", ());
let pl = make(~color=Color.primaryLight, ());
let bpl = make(~color=Color.brandColor, ());
let f_pl = make(~fill=Color.primaryLight, ());
let square = size => make(~width=px(size), ~height=px(size), ());
