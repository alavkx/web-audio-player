open Util;
requireCSS("./Library.css");

type event =
  | FocusRow(int)
  | Next
  | Previous
  | Blur
  | TriggerEffect
  | NoOp;
type status =
  | None
  | First
  | Middle(int)
  | Last(int);
let posOfArray = (index: int, xs: array('a)) =>
  switch (index) {
  | 0 => First
  | i when i >= Array.length(xs) - 1 => Last(i)
  | i => Middle(i)
  };
let valOfPos = (p: status) =>
  switch (p) {
  | None
  | First => 0
  | Middle(i)
  | Last(i) => i
  };
let eqPos = (n: int, p: status) =>
  switch (p) {
  | None => false
  | First => n == 0
  | Middle(i)
  | Last(i) => i == n
  };
type state = {status};
let handleKeyboardEvent = (e: ReactEvent.Keyboard.t) =>
  switch (ReactEvent.Keyboard.key(e)) {
  | "ArrowDown" => Next
  | "ArrowUp" => Previous
  | "Enter" => TriggerEffect
  | "Escape" => Blur
  | _ => NoOp
  };
[@react.component]
let make = (~tracks: array(Track.t), ~playTrack: int => unit) => {
  let (state, send) =
    React.useReducer(
      (state, event) =>
        switch (state.status, event) {
        | (_, FocusRow(i)) => {status: posOfArray(i, tracks)}
        | (_, Blur) => {status: None}
        | (Last(i) | Middle(i), Previous) => {
            status: posOfArray(i - 1, tracks),
          }
        | (First, Next) => {status: Middle(1)}
        | (Middle(i), Next) => {status: posOfArray(i + 1, tracks)}
        | (None, Next | Previous) => {status: First}
        | (First, Previous)
        | (Last(_), Next)
        | (_, NoOp)
        | (_, TriggerEffect) => state
        },
      {status: None},
    );
  <table
    className="library"
    tabIndex=0
    onKeyDown={e =>
      switch (handleKeyboardEvent(e)) {
      | TriggerEffect => state.status->valOfPos->playTrack
      | (Next | Previous | NoOp | FocusRow(_) | Blur) as x => send(x)
      }
    }
    onFocus={_e => send(FocusRow(0))}
    onBlur={_e => send(Blur)}>
    <tbody>
      {React.array(
         Array.mapi(
           (i, {artist, name}: Track.t) =>
             <tr
               style={ReactDOMRe.Style.make(
                 ~borderColor=eqPos(i, state.status) ? "blue" : "grey",
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