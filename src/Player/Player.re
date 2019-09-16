open Util;
requireCSS("./Player.css");

type status =
  | Stopped
  | Playing
  | Rewinding
  | FastForwarding
  | Paused;
type state = {
  status,
  activeTrackIndex: option(int),
};
type transition =
  | PlayTrack(int)
  | PlayPause
  | Stop
  | FastForward
  | Rewind
  | DoNothing;
[@react.component]
let make = (~tracks: array(Track.t)) => {
  let (state, send) =
    React.useReducer(
      (state, event) =>
        switch (state.status, event) {
        | (_, PlayTrack(i)) => {activeTrackIndex: Some(i), status: Playing}
        | (Stopped, PlayPause) => {
            activeTrackIndex: Some(0),
            status: Playing,
          }
        | (Paused | Rewinding | FastForwarding, PlayPause) => {
            ...state,
            status: Playing,
          }
        | (Playing, PlayPause) => {...state, status: Paused}
        | (Paused | Playing | Rewinding | FastForwarding, Rewind) => {
            ...state,
            status: Rewinding,
          }
        | (Paused | Playing | Rewinding | FastForwarding, FastForward) => {
            ...state,
            status: FastForwarding,
          }
        | (_, Stop) => {activeTrackIndex: None, status: Stopped}
        | (Stopped, FastForward | Rewind)
        | (_, DoNothing) => state
        },
      {activeTrackIndex: None, status: Stopped},
    );
  <>
    <Library tracks playTrack={i => send(PlayTrack(i))} />
    <nav>
      <main>
        {str(
           switch (state.activeTrackIndex) {
           | None => "Play a song, stupid"
           | Some(i) => "Now playing: " ++ tracks[i].name
           },
         )}
      </main>
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
          <button onClick={_ => send(PlayPause)} className="playpause">
            {str(
               switch (state.status) {
               | Rewinding
               | FastForwarding
               | Paused
               | Stopped => "Play"
               | Playing => "Pause"
               },
             )}
          </button>
          <button onClick={_ => send(Stop)} className="stop">
            {str("Stop")}
          </button>
          <button onClick={_ => send(Rewind)} className="rwd">
            {str("Rwd")}
          </button>
          <button onClick={_ => send(FastForward)} className="fwd">
            {str("Fwd")}
          </button>
          <div className="time"> {str("00:00")} </div>
        </div>
      </section>
    </nav>
  </>;
};