open Util;
requireCSS("./Library.css");

type event =
  | FocusRow(int)
  | Next
  | Previous
  | TriggerEffect
  | NoOp;
type status =
  | First
  | Middle
  | Last;
let posOfArray = (index: int, xs: array('a)) =>
  switch (index) {
  | 0 => First
  | x when x >= Array.length(xs) - 1 => Last
  | _ => Middle
  };
type state = {
  status,
  focusedTrackIndex: int,
};
let handleKeyboardEvent = (e: ReactEvent.Keyboard.t) =>
  switch (ReactEvent.Keyboard.key(e)) {
  | "ArrowDown" => Next
  | "ArrowUp" => Previous
  | "Enter" => TriggerEffect
  | _ => NoOp
  };
[@react.component]
let make = (~tracks: array(Track.t), ~playTrack: int => unit) => {
  let (state, send) =
    React.useReducer(
      (state, event) =>
        switch (state.status, event) {
        | (_, FocusRow(i)) => {
            focusedTrackIndex: i,
            status: posOfArray(i, tracks),
          }
        | (Last | Middle, Previous) =>
          let nextId = state.focusedTrackIndex - 1;
          {focusedTrackIndex: nextId, status: posOfArray(nextId, tracks)};
        | (First | Middle, Next) =>
          let nextId = state.focusedTrackIndex + 1;
          {focusedTrackIndex: nextId, status: posOfArray(nextId, tracks)};
        | (First, Previous)
        | (Last, Next)
        | (_, NoOp)
        | (_, TriggerEffect) => state
        },
      {focusedTrackIndex: 0, status: First},
    );
  <table
    className="library"
    tabIndex=0
    onKeyDown={e =>
      switch (handleKeyboardEvent(e)) {
      | TriggerEffect => playTrack(state.focusedTrackIndex)
      | (Next | Previous | NoOp | FocusRow(_)) as x => send(x)
      }
    }>
    <tbody>
      {React.array(
         Array.mapi(
           (i, {artist, name}: Track.t) =>
             <tr
               style={ReactDOMRe.Style.make(
                 ~backgroundColor=
                   state.focusedTrackIndex == i ? "blue" : "white",
                 (),
               )}
               key={string_of_int(i)}
               onClick={_ => send(FocusRow(i))}
               onDoubleClick={_ => playTrack(i)}>
               <td> {str(artist)} </td>
               <td> {str(name)} </td>
             </tr>,
           tracks,
         ),
       )}
    </tbody>
  </table>;
};