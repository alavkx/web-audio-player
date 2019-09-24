open Util;
requireCSS("./Player.css");

type status =
  | Stopped
  | Playing
  | Rewinding
  | FastForwarding
  | Paused;
type event =
  | PlayTrack(int)
  | PlayPause
  | Stop
  | FastForward
  | Rewind
  | Identity;
type state = {
  status,
  currentTime: int,
  activeTrackIndex: option(int),
};
[@react.component]
let make = (~tracks: array(Track.t)) => {
  let playerRef = React.useRef(Js.Nullable.null);
  let (state, send) =
    React.useReducer(
      (state, event) =>
        switch (state.status, event) {
        | (_, PlayTrack(i)) => {
            ...state,
            activeTrackIndex: Some(i),
            status: Playing,
          }
        | (Stopped, PlayPause) => {
            ...state,
            activeTrackIndex: Some(0),
            status: Playing,
          }
        | (Playing, PlayPause) => {...state, status: Paused}
        | (Paused | Rewinding | FastForwarding, PlayPause) => {
            ...state,
            status: Playing,
          }
        | (Paused | Playing | Rewinding | FastForwarding, Rewind) => {
            ...state,
            status: Rewinding,
          }
        | (Paused | Playing | Rewinding | FastForwarding, FastForward) => {
            ...state,
            status: FastForwarding,
          }
        | (_, Stop) => {
            activeTrackIndex: None,
            status: Stopped,
            currentTime: 0,
          }
        | (Stopped, FastForward | Rewind)
        | (_, Identity) => state
        },
      {activeTrackIndex: None, status: Stopped, currentTime: 0},
    );
  React.useEffect1(
    () => {
      switch (playerRef->React.Ref.current->Js.Nullable.toOption) {
      | None => ()
      | Some(node) =>
        let current = ReactDOMRe.domElementToObj(node);
        current##currentTime #= state.currentTime;
      };
      None;
    },
    [|state.currentTime|],
  );
  React.useEffect2(
    () => {
      switch (playerRef->React.Ref.current->Js.Nullable.toOption) {
      | None => ()
      | Some(node) =>
        let current = ReactDOMRe.domElementToObj(node);
        switch (state.status) {
        | Stopped
        | Paused => current##pause()
        | Playing => current##play()
        | Rewinding => send(Rewind)
        | FastForwarding => send(FastForward)
        };
      };
      None;
    },
    (state.status, state.currentTime),
  );
  // React.useEffect1(() => {
  // let timeoutId = Js.Global.setTimeout(() => setTracks(_ => Some(persistedTracks)), 1000);
  // Some(() => Js.Global.clearTimeout(timeoutId))
  // }, [||])
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
        <audio ref={ReactDOMRe.Ref.domRef(playerRef)}>
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
          <div className="time"> {state.currentTime->string_of_int->str} </div>
        </div>
      </section>
    </nav>
  </>;
};