type buffer = {
  .
  "start": float,
  "end": float,
};
type state = {
  .
  "buffered": array(buffer),
  "time": float,
  "duration": float,
  "paused": bool,
  "muted": bool,
  "volume": float,
};
type controls = {
  .
  [@bs.meth] "play": unit => Js.Nullable.t(Js.Promise.t(unit)),
  [@bs.meth] "pause": unit => unit,
  [@bs.meth] "mute": unit => unit,
  [@bs.meth] "unmute": unit => unit,
  [@bs.meth] "volume": float => unit,
  [@bs.meth] "seek": float => unit,
};
[@bs.deriving abstract]
type config = {
  src: string,
  autoPlay: bool,
};
[@bs.module "react-use"]
external useAudio: config => (React.element, state, controls) = "useAudio";