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
type controls;
// [@bs.deriving abstract]
// type controls = {
//   play: () => option(Js.Promise(unit)),
//   pause: () => unit,
//   mute: () => unit,
//   unmute: () => unit,
//   volume: number => unit,
//   seek: number => unit,
// };

[@bs.module "react-use"]
external useAudio: config => (React.element, state, controls) = "useAudio";