open Util;
requireCSS("./Player.css");
type status =
  | Paused
  | Playing;
type event =
  | PlayTrack(int)
  | TogglePlayPause;
let nextStrOfStatus = s =>
  switch (s) {
  | Paused => "Play"
  | Playing => "Pause"
  };
type state = {
  status,
  activeTrackIndex: option(int),
};
let timeOfFloat = (secondsTotal: float) => {
  let minutes = secondsTotal /. 60. |> int_of_float;
  let hours = minutes / 60;
  let seconds = mod_float(secondsTotal, 60.)->int_of_float;
  let strOfTime = x =>
    switch (x) {
    | 0 => ""
    | x => string_of_int(x) ++ ":"
    };
  strOfTime(hours) ++ strOfTime(minutes) ++ string_of_int(seconds);
};
[@react.component]
let make = (~tracks: array(Track.t)) => {
  let (state, send) =
    React.useReducer(
      (state, event) =>
        switch (state.status, event) {
        | (_, PlayTrack(i)) => {activeTrackIndex: Some(i), status: Playing}
        | (Paused, TogglePlayPause) => {
            activeTrackIndex:
              switch (state.activeTrackIndex) {
              | None => Some(0)
              | Some(i) => Some(i)
              },
            status: Playing,
          }
        | (Playing, TogglePlayPause) => {...state, status: Paused}
        },
      {status: Paused, activeTrackIndex: None},
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
  React.useEffect2(
    () => {
      switch (state.status) {
      | Playing => controls##play()->ignore
      | Paused => controls##pause()
      };
      None;
    },
    (state.status, controls),
  );
  <>
    <Library tracks playTrack={i => send(PlayTrack(i))} />
    <section ariaLabel="player">
      audio
      <div className="controls">
        <button onClick={_e => send(TogglePlayPause)}>
          {nextStrOfStatus(state.status)->str}
        </button>
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
        {playerState##time->timeOfFloat->str}
        {playerState##muted
           ? <button onClick={_e => controls##unmute()}>
               {str("Un-mute")}
             </button>
           : <button onClick={_e => controls##mute()}> {str("Mute")} </button>}
        {playerState##volume
         *. 100.0
         |> Js.Float.toFixed
         |> Js.String.concat("%")
         |> str}
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
  </>;
};