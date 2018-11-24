open BsStorybook.Story;
open Styles;
open StoryUtils;

let _module = [%bs.raw "module"];
let highlightText = "Contemplating these essential landscapes, Kublai reflected on the invisible order that sustains cities, on the rules that decreed how they rise, take shape and prosper, adapting themselves to the seasons, and then how they sadden and fall in ruins.";
let makeData = () =>
  Array.init(20, _idx =>
    ("Invisible Cities", "Italo Calvino", highlightText)
  );

module MakeListPaginator =
       (
         ListSpec: {
           type data;
           let onPaginate: option(data) => data;
           let render:
             (
               ~data: data,
               ~onPaginate: unit => Js.Nullable.t(Js.Promise.t(unit)),
               unit
             ) =>
             ReasonReact.reactElement;
         },
       ) => {
  type state = {
    data: ListSpec.data,
    pageNumber: int,
  };
  type action =
    | AddData;
  let component = ReasonReact.reducerComponent("ListPaginator");
  let make = _children => {
    ...component,
    initialState: () => {data: ListSpec.onPaginate(None), pageNumber: 1},
    reducer: (action, state) =>
      switch (action) {
      | AddData =>
        ReasonReact.Update({
          data: ListSpec.onPaginate(Some(state.data)),
          pageNumber: state.pageNumber + 1,
        })
      },
    render: self => {
      let onEndReached = () =>
        if (self.state.pageNumber < 5) {
          self.send(AddData);
          Js.Nullable.return(Js.Promise.resolve());
        } else {
          Js.Nullable.null;
        };
      ListSpec.render(~data=self.state.data, ~onPaginate=onEndReached, ());
    },
  };
};

storiesOf("Components/Lists", _module)
->(
    add("InfiniteList", () => {
      module ListPaginator =
        MakeListPaginator({
          type data = array((string, string, string));
          let onPaginate = data =>
            Array.append(Js.Option.getWithDefault([||], data), makeData());
          let render = (~data, ~onPaginate, ()) =>
            <AppFrame>
              <div
                className={cn(["flex", "flex-auto", "relative"])}
                style={make(~width=px(400), ~height=px(350), ())}>
                <InfiniteList
                  data
                  className={cn(["ph3"])}
                  renderItem={
                    ((title, author, text)) =>
                      <HighlightListItem
                        onShareClicked={() => ()}
                        title
                        author
                        text
                      />
                  }
                  renderSeparator={() => <div className={cn(["mv3"])} />}
                  endThreshold=4.0
                  onEndReached=onPaginate
                />
              </div>
            </AppFrame>;
        });

      <ListPaginator />;
    })
  )
->(
    add("SectionList", () => {
      module ListPaginator =
        MakeListPaginator({
          type section = {
            header: string,
            data: array((string, string, string)),
          };
          type data = array(section);

          let onPaginate = data =>
            switch (data) {
            | Some(arr) =>
              Js.Array.mapi(
                (section, idx) =>
                  if (idx === Array.length(arr) - 1) {
                    {
                      ...section,
                      data: Array.append(section.data, makeData()),
                    };
                  } else {
                    section;
                  },
                arr,
              )
            | None => [|
                {header: "Highlights One", data: makeData()},
                {header: "Highlights Two", data: makeData()},
              |]
            };

          let render = (~data, ~onPaginate, ()) =>
            <AppFrame>
              <div
                className={cn(["flex", "flex-auto", "relative"])}
                style={make(~width=px(500), ~height=px(600), ())}>
                <SectionList
                  data
                  onEndReached=onPaginate
                  endThreshold=3.0
                  className={cn(["ph3"])}
                  renderSeparator={() => <div className={cn(["mv3"])} />}
                  renderSectionHeader={
                    ({header}) =>
                      <div className={cn(["f3", "mt5", "mb4", "pl", "b"])}>
                        {ReasonReact.string(header)}
                      </div>
                  }
                  renderItem={
                    ({data}) => {
                      let items =
                        Js.Array.mapi(
                          ((title, author, text), idx) =>
                            <>
                              <HighlightListItem
                                onShareClicked={() => ()}
                                title
                                author
                                text
                              />
                              {
                                idx < Js.Array.length(data) - 1 ?
                                  <div className={cn(["mv2"])} /> :
                                  ReasonReact.null
                              }
                            </>,
                          data,
                        );
                      <div className={cn(["flex", "flex-column"])}>
                        ...items
                      </div>;
                    }
                  }
                />
              </div>
            </AppFrame>;
        });

      <ListPaginator />;
    })
  );
