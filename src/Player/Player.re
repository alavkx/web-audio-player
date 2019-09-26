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
  <div
    onKeyDown={(e: ReactEvent.Keyboard.t) =>
      switch (ReactEvent.Keyboard.key(e)) {
      | "ArrowLeft" => controls##seek(playerState##time -. 5.0)
      | "ArrowRight" => controls##seek(playerState##time +. 5.0)
      | _ => ()
      }
    }>
    <Library tracks playTrack={i => send(PlayTrack(i))} />
    <section ariaLabel="player">
      audio
      <div className="controls">
        {playerState##pause
           ? <button onClick={_e => controls##pause()}>
               {str("Pause")}
             </button>
           : <button onClick={_e => controls##play() |> ignore}>
               {str("Play")}
             </button>}
        <input
          type_="range"
          value={Js.Float.toString(playerState##time)}
          onChange={(e: ReactEvent.Form.t) =>
            controls##seek(ReactEvent.Form.target(e)##value)
          }
          min=0
          max={Js.Float.toString(playerState##duration)}
          step=1.0
        />
        {playerState##muted
           ? <button onClick={_e => controls##unmute()}>
               {str("Un-mute")}
             </button>
           : <button onClick={_e => controls##mute()}> {str("Mute")} </button>}
        {str(
           "Volume" ++ Js.Float.toFixed(playerState##volume *. 100.0) ++ "%",
         )}
        <input
          type_="range"
          value={Js.Float.toString(playerState##volume)}
          onChange={(e: ReactEvent.Form.t) =>
            controls##volume(ReactEvent.Form.target(e)##value)
          }
          min=0
          max="1"
          step=0.01
        />
      </div>
    </section>
  </div>;
};