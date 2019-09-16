open Util;
requireCSS("./App.css");

let persistedTracks: array(Track.t) = [|
  {artist: "Kromestar", name: "007"},
  {artist: "Kromestar", name: "008"},
  {artist: "Kromestar", name: "009"},
  {artist: "Kromestar", name: "010"},
  {artist: "Kromestar", name: "011"},
  {artist: "Kromestar", name: "012"},
  {artist: "Kromestar", name: "013"},
|];
// type state = { };
// type event = |?;
[@react.component]
let make = () => {
  let (tracks: option(array(Track.t)), setTracks) =
    React.useState(() => None);
  React.useEffect1(
    () => {
      let timeoutId =
        Js.Global.setTimeout(
          () => setTracks(_ => Some(persistedTracks)),
          500,
        );
      Some(() => Js.Global.clearTimeout(timeoutId));
    },
    [|setTracks|],
  );
  switch (tracks) {
  | Some(tracks) => <Player tracks />
  | None => str("Booting up the most incredible experience of your life...")
  };
};