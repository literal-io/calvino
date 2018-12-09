type state = {
  document: option(JavamonnBsLibrarian.DocumentModel.t),
  activity: option(ProfileSection.activity),
};

type actions =
  | SetDocument(option(JavamonnBsLibrarian.DocumentModel.t))
  | SetActivity(option(ProfileSection.activity));

let component = ReasonReact.reducerComponent("ProfileSectionContainer");

let make = (~readerPath, _children) => {
  ...component,
  initialState: () => {document: None, activity: None},
  reducer: (action, state) =>
    switch (action) {
    | SetDocument(document) => ReasonReact.Update({...state, document})
    | SetActivity(activity) => ReasonReact.Update({...state, activity})
    },
  didMount: _self => {
    let _ =
      JavamonnBsLibrarian.(
        FindService.UserReadActivity.findOne(
          ~query=
            LibrarianFind.q(
              ~type_=UserReadActivityModel.activityTypeToJs(`DocumentOpen),
              ~owner=LibrarianUtils.sha256(userProfileId),
              (),
            ),
          ~cursor=
            LibrarianFind.makeCursor(
              ~limit=Js.Nullable.return(1),
              ~sort=Js.Nullable.return("-createdAt"),
              (),
            ),
          (),
        )
      );
    ();
  },
  render: _self =>
    <ProfileSection
      readerPath
      document={self.state.document}
      activity={self.state.activity}
    />,
};
