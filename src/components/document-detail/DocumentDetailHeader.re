open Styles;

type state = {
  dirtyTitle: string,
  dirtyAuthor: string,
  title: string,
  author: string,
};

type action =
  | TitleChange(string)
  | AuthorChange(string)
  | Reset;

let component = ReasonReact.reducerComponent("DocumentDetailHeader");

let make = (~title, ~author, ~onTitleChange, ~onAuthorChange, _children) => {
  ...component,
  initialState: () => {title, author, dirtyAuthor: author, dirtyTitle: title},
  reducer: (action, state) =>
    switch (action) {
    | TitleChange(title) => ReasonReact.Update({...state, dirtyTitle: title})
    | AuthorChange(author) =>
      ReasonReact.Update({...state, dirtyAuthor: author})
    | Reset =>
      ReasonReact.Update({
        title,
        author,
        dirtyTitle: title,
        dirtyAuthor: author,
      })
    },
  willReceiveProps: self => {
    let resetTitle = title !== self.state.title;
    let resetAuthor = title !== self.state.author;
    {
      title: resetTitle ? title : self.state.title,
      dirtyTitle: resetTitle ? title : self.state.dirtyTitle,
      author: resetAuthor ? author : self.state.author,
      dirtyAuthor: resetAuthor ? author : self.state.dirtyAuthor,
    };
  },
  render: self =>
    <div className={cn(["flex", "flex-column"])}>
      <MaterialUi.TextField
        value={`String(self.state.dirtyTitle)}
        label={ReasonReact.string("Title")}
        fullWidth=true
        multiline=true
        onChange={ev =>
          self.send(TitleChange(ReactEvent.Form.target(ev)##value))
        }
        onBlur={_ev => {
          if (self.state.dirtyTitle !== self.state.title) {
            let _ = onTitleChange(self.state.dirtyTitle);
          };
          ();
        }}
        _InputLabelProps={
          "classes": {
            "root": "w-o5",
            "focused": "accent-i",
          },
        }
        _InputProps={
          "classes": {
            "root": "pl f3",
            "underline": "b-sl-before-i b-accent-after-i",
          },
        }
      />
      <Spacer size=3 />
      <MaterialUi.TextField
        value={`String(self.state.dirtyAuthor)}
        label={ReasonReact.string("Author")}
        onChange={ev =>
          self.send(AuthorChange(ReactEvent.Form.target(ev)##value))
        }
        onBlur={_ev => {
          if (self.state.dirtyAuthor !==  self.state.author) {
            let _ = onAuthorChange(self.state.author);
          };
          ();
        }}
        fullWidth=true
        multiline=true
        _InputLabelProps={
          "classes": {
            "root": "w-o5",
            "focused": "accent-i",
          },
        }
        _InputProps={
          "classes": {
            "root": "pl f4",
            "underline": "b-sl-before-i b-accent-after-i",
          },
        }
      />
    </div>,
};
