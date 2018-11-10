open BsStorybook.Story;

let _module = [%bs.raw "module"];

storiesOf("Components", _module)
  |. add("Component1", () => <Component1 message="Hello, World!" />);
