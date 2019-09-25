type buffer = {
  start: float,
  _end: float,
};
type state = {
  buffered: array(buffer),
  time: float,
  duration: float,
  pause: bool,
  muted: bool,
  volume: float,
};
[@bs.deriving abstract]
type config = {
  src: string,
  autoPlay: bool,
};
type controls = {
  play: unit => Js.Nullable.t(Js.Promise.t(unit)),
  pause: unit => unit,
  mute: unit => unit,
  unmute: unit => unit,
  volume: float => unit,
  seek: float => unit,
};

[@bs.module "react-use"]
external useAudio: config => (React.element, state, controls) = "useAudio";