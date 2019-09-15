type track = {
  name: string,
  artist: string,
};
let tracks = [|
  {artist: "Kromestar", name: "007"},
  {artist: "Kromestar", name: "008"},
  {artist: "Kromestar", name: "009"},
  {artist: "Kromestar", name: "010"},
  {artist: "Kromestar", name: "011"},
  {artist: "Kromestar", name: "012"},
  {artist: "Kromestar", name: "013"},
|];
type rowStatus =
  | First
  | Middle
  | Last;
let getRowStatus = (index: int, xs: array('a)) =>
  switch (index) {
  | 0 => First
  | x when x >= Array.length(xs) - 1 => Last
  | _ => Middle
  };
type state = {
  selectedRowIndex: int,
  rowStatus,
};
type event =
  | SelectRow(int)
  | MoveUp
  | MoveDown
  | DoNothing;
let keyboardEvent = (e: ReactEvent.Keyboard.t) =>
  switch (ReactEvent.Keyboard.key(e)) {
  | "ArrowUp" => MoveUp
  | "ArrowDown" => MoveDown
  | _ => DoNothing
  };
[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, event) =>
        switch (state.rowStatus, event) {
        | (_, SelectRow(index)) => {
            selectedRowIndex: index,
            rowStatus: getRowStatus(index, tracks),
          }
        | (Last | Middle, MoveUp) =>
          let nextId = state.selectedRowIndex - 1;
          {
            selectedRowIndex: nextId,
            rowStatus: getRowStatus(nextId, tracks),
          };
        | (First | Middle, MoveDown) =>
          let nextId = state.selectedRowIndex + 1;
          {
            selectedRowIndex: nextId,
            rowStatus: getRowStatus(nextId, tracks),
          };
        | (First, MoveUp)
        | (Last, MoveDown)
        | (_, DoNothing) => state
        },
      {selectedRowIndex: 0, rowStatus: First},
    );
  <table tabIndex=0 onKeyDown={e => dispatch(keyboardEvent(e))}>
    {React.array(
       Array.mapi(
         (i, {artist, name}) =>
           <tr
             style={ReactDOMRe.Style.make(
               ~backgroundColor=state.selectedRowIndex == i ? "blue" : "white",
               (),
             )}
             key={string_of_int(i)}
             onClick={_ => dispatch(SelectRow(i))}>
             <td> {ReasonReact.string(artist)} </td>
             <td> {ReasonReact.string(name)} </td>
           </tr>,
         tracks,
       ),
     )}
  </table>;
};