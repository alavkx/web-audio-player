open Util;
requireCSS("./Library.css");

type position =
  | First
  | Middle
  | Last;
let getPosition = (index: int, xs: array('a)) =>
  switch (index) {
  | 0 => First
  | x when x >= Array.length(xs) - 1 => Last
  | _ => Middle
  };
type state = {
  focusedTrackIndex: int,
  status: position,
};
type event =
  | FocusRow(int)
  | Next
  | Previous
  | TriggerEffect
  | DoNothing;
let handleKeyboardEvent = (e: ReactEvent.Keyboard.t) =>
  switch (ReactEvent.Keyboard.key(e)) {
  | "ArrowDown" => Next
  | "ArrowUp" => Previous
  | "Enter" => TriggerEffect
  | _ => DoNothing
  };
[@react.component]
let make = (~tracks: array(Track.t), ~playTrack: int => unit) => {
  let (state, send) =
    React.useReducer(
      (state, event) =>
        switch (state.status, event) {
        | (_, FocusRow(i)) => {
            focusedTrackIndex: i,
            status: getPosition(i, tracks),
          }
        | (Last | Middle, Previous) =>
          let nextId = state.focusedTrackIndex - 1;
          {focusedTrackIndex: nextId, status: getPosition(nextId, tracks)};
        | (First | Middle, Next) =>
          let nextId = state.focusedTrackIndex + 1;
          {focusedTrackIndex: nextId, status: getPosition(nextId, tracks)};
        | (First, Previous)
        | (Last, Next)
        | (_, DoNothing)
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
      | x => send(x)
      }
    }>
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
  </table>;
};