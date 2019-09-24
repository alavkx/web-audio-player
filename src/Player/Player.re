open Util;
requireCSS("./Player.css");
type status =
  | Stopped;
type event =
  | PlayTrack(int);
type state = {
  status,
  activeTrackIndex: option(int),
};
[@react.component]
let make = (~tracks: array(Track.t)) => {
  let (_state, send) =
    React.useReducer(
      (state, event) =>
        switch (state.status, event) {
        | (Stopped, PlayTrack(i)) => {...state, activeTrackIndex: Some(i)}
        },
      {status: Stopped, activeTrackIndex: None},
    );
  let (audio, playerState, controls) =
    ReactUse.useAudio(
      ReactUse.config(
        ~src=
          "/Users/alavkx/Projects/reasonml-test/static/Skepta - Nasty (Kelly Dean Bootleg Remix).wav",
        ~autoPlay=false,
      ),
    );
  <>
    <Library tracks playTrack={i => send(PlayTrack(i))} />
    <section ariaLabel="player">
      audio
      <div className="controls">
        <button onClick={controls.pause}> {str("Pause")} </button>
        <button onClick={controls.play}> {str("Play")} </button>
        <button onClick={controls.mute}> {str("Mute")} </button>
        <button onClick={controls.unmute}> {str("Un-mute")} </button>
        <input type_="range" onChange={() => controls.volume(0.5)}>
          {str("Volume: 50%")}
        </input>
        <button onClick={() => controls.seek(state.time - 5)}>
          {str("-5 sec")}
        </button>
        <button onClick={() => controls.seek(state.time + 5)}>
          {str("+5 sec")}
        </button>
      </div>
    </section>
  </>;
};