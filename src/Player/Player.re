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
  let (state, send) =
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
        ~src={
          switch (state.activeTrackIndex) {
          | Some(i) => tracks[i].src
          | None => ""
          };
        },
        ~autoPlay=false,
      ),
    );
  <>
    <Library tracks playTrack={i => send(PlayTrack(i))} />
    <section
      ariaLabel="player"
      onKeyDown={(e: ReactEvent.Keyboard.t) =>
        switch (ReactEvent.Keyboard.key(e)) {
        | "ArrowLeft" => controls##seek(playerState##time -. 5.0)
        | "ArrowRight" => controls##seek(playerState##time +. 5.0)
        | _ => ()
        }
      }>
      <div className="controls">
        audio
        <button onClick={_e => controls##pause()}> {str("Pause")} </button>
        <button onClick={_e => controls##play() |> ignore}>
          {str("Play")}
        </button>
        <button onClick={_e => controls##mute()}> {str("Mute")} </button>
        <button onClick={_e => controls##unmute()}> {str("Un-mute")} </button>
        <input
          type_="range"
          onChange={(e: ReactEvent.Form.t) =>
            controls##volume(ReactEvent.Form.target(e)##value)
          }
          min=0
          max="1"
          step=0.01
        />
      </div>
    </section>
  </>;
};