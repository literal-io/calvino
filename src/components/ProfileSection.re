open Styles;
let component = ReasonReact.statelessComponent("ProfileSection");

let make = (_children) => {
  ...component,
  render: (_self) => {
    <div className={cn(["flex", "flex-row"])}>
      <div style={flex(4)} className={cn(["flex-auto"])}> 
        { /** TODO: Activity */ } 
      </div>
      <div style={flex(6)} className={cn(["flex", "flex-column"])}>
        <div style={flex(7)}>
          { /** TODO: Resume Reading */ }
        </div>
        <div style={flex(3)} className={cn(["flex", "flex-row"])}>
          <div style={flex(3)}>
            { /** TODO: Settings */ }
          </div>
          <div style={flex(6)}>
            { /** TODO: Feedback */
          </div>
        </div>
      </div>
    </div>
  }
}
