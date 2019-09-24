// [@bs.deriving abstract]
// type buffer = {
//   start: float,
//   _end: float,
// };
// [@bs.deriving abstract];
// type state = {
//   buffered: array(buffer),
//   time: float,
//   duration: float,
//   pause: bool,
//   muted: bool,
//   volume: float,
// };
[@bs.deriving abstract]
type config = {
  src: string,
  autoPlay: bool,
};
type state;
type controls = {
  .
  "play": ReactEvent.Mouse.t => Js.Nullable.t(Js.Promise.t(unit)),
  "pause": ReactEvent.Mouse.t => unit,
  "mute": ReactEvent.Mouse.t => unit,
  "unmute": ReactEvent.Mouse.t => unit,
  "volume": float => unit,
  "seek": float => unit,
};

[@bs.module "react-use"]
external useAudio: config => (React.element, state, controls) = "useAudio";