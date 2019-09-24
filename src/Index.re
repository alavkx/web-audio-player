module App = {
  open Util;
  requireCSS("./App.css");

  let persistedTracks: array(Track.t) = [|
    {
      artist: "Kromestar",
      name: "007",
      src: "/Users/alavkx/Projects/reasonml-test/static/Skepta - Nasty (Kelly Dean Bootleg Remix).wav",
    },
    {
      artist: "Kromestar",
      name: "008",
      src: "/Users/alavkx/Projects/reasonml-test/static/Skepta - Nasty (Kelly Dean Bootleg Remix).wav",
    },
    {
      artist: "Kromestar",
      name: "009",
      src: "/Users/alavkx/Projects/reasonml-test/static/Skepta - Nasty (Kelly Dean Bootleg Remix).wav",
    },
    {
      artist: "Kromestar",
      name: "0010",
      src: "/Users/alavkx/Projects/reasonml-test/static/Skepta - Nasty (Kelly Dean Bootleg Remix).wav",
    },
  |];
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
};
ReactDOMRe.renderToElementWithId(<App />, "root");