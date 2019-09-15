let str = ReasonReact.string;
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
  selectedRowIndex: int,
  rowStatus: position,
  activeTrackIndex: option(int),
  playing: bool,
};
type event =
  | FocusRow(int)
  | Next
  | Previous
  | PlayTrack(option(int))
  | TogglePlaying
  // | Stop
  | DoNothing;
let keyboardEvent = (e: ReactEvent.Keyboard.t) =>
  switch (ReactEvent.Keyboard.key(e)) {
  | "ArrowDown" => Next
  | "ArrowUp" => Previous
  | _ => DoNothing
  };
[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, event) =>
        switch (state.rowStatus, event) {
        | (_, FocusRow(index)) => {
            ...state,
            selectedRowIndex: index,
            rowStatus: getPosition(index, tracks),
          }
        | (Last | Middle, Previous) =>
          let nextId = state.selectedRowIndex - 1;
          {
            ...state,
            selectedRowIndex: nextId,
            rowStatus: getPosition(nextId, tracks),
          };
        | (First | Middle, Next) =>
          let nextId = state.selectedRowIndex + 1;
          {
            ...state,
            selectedRowIndex: nextId,
            rowStatus: getPosition(nextId, tracks),
          };
        | (_, PlayTrack(i)) => {...state, activeTrackIndex: i}
        | (_, TogglePlaying) => {...state, playing: !state.playing}
        | (First, Previous)
        | (Last, Next)
        | (_, DoNothing) => state
        },
      {
        selectedRowIndex: 0,
        rowStatus: First,
        activeTrackIndex: None,
        playing: false,
      },
    );
  <>
    <table tabIndex=0 onKeyDown={e => dispatch(keyboardEvent(e))}>
      {React.array(
         Array.mapi(
           (i, {artist, name}) =>
             <tr
               style={ReactDOMRe.Style.make(
                 ~backgroundColor=
                   state.selectedRowIndex == i ? "blue" : "white",
                 (),
               )}
               key={string_of_int(i)}
               onClick={_ => dispatch(FocusRow(i))}
               onDoubleClick={_ => dispatch(PlayTrack(Some(i)))}>
               <td> {str(artist)} </td>
               <td> {str(name)} </td>
             </tr>,
           tracks,
         ),
       )}
    </table>
    <nav>
      <section ariaLabel="player">
        <audio controls=true>
          <source src="viper.mp3" type_="audio/mp3" />
          <p>
            {str("Your browser doesn't support HTML5 video. Here is a ")}
            <a href="rabbit320.mp4"> {str("link to the video ")} </a>
            {str("instead.")}
          </p>
        </audio>
        <div className="controls">
          <button
            onClick={_ => dispatch(TogglePlaying)} className="playpause">
            {str(state.playing ? "Pause" : "Play")}
          </button>
          <button className="stop"> {str("Stop")} </button>
          <button className="rwd"> {str("Rwd")} </button>
          <button className="fwd"> {str("Fwd")} </button>
          <div className="time"> {str("00:00")} </div>
        </div>
      </section>
      <main>
        {str(
           switch (state.activeTrackIndex) {
           | None => "Play a song, stupid"
           | Some(i) => "Now playing: " ++ tracks[i].name
           },
         )}
      </main>
    </nav>
  </>;
};