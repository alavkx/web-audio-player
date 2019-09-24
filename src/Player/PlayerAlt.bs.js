// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Util$ReactHooksTemplate = require("../Util.bs.js");
var Library$ReactHooksTemplate = require("../Library/Library.bs.js");

require("./Player.css");

function PlayerAlt(Props) {
  var tracks = Props.tracks;
  var playerRef = React.useRef(null);
  var match = React.useReducer((function (state, $$event) {
          var match = state[/* status */0];
          var exit = 0;
          if (typeof $$event === "number") {
            if ($$event !== 1) {
              if ($$event >= 4) {
                return state;
              } else if (match !== 1) {
                if (match !== 0) {
                  if ($$event >= 2) {
                    exit = 1;
                  } else {
                    return /* record */[
                            /* status : Playing */1,
                            /* currentTime */state[/* currentTime */1],
                            /* activeTrackIndex */state[/* activeTrackIndex */2]
                          ];
                  }
                } else if ($$event >= 2) {
                  return state;
                } else {
                  return /* record */[
                          /* status : Playing */1,
                          /* currentTime */state[/* currentTime */1],
                          /* activeTrackIndex */0
                        ];
                }
              } else if ($$event >= 2) {
                exit = 1;
              } else {
                return /* record */[
                        /* status : Paused */4,
                        /* currentTime */state[/* currentTime */1],
                        /* activeTrackIndex */state[/* activeTrackIndex */2]
                      ];
              }
            } else {
              return /* record */[
                      /* status : Stopped */0,
                      /* currentTime */0,
                      /* activeTrackIndex */undefined
                    ];
            }
          } else {
            return /* record */[
                    /* status : Playing */1,
                    /* currentTime */state[/* currentTime */1],
                    /* activeTrackIndex */$$event[0]
                  ];
          }
          if (exit === 1) {
            if ($$event >= 3) {
              return /* record */[
                      /* status : Rewinding */2,
                      /* currentTime */state[/* currentTime */1],
                      /* activeTrackIndex */state[/* activeTrackIndex */2]
                    ];
            } else {
              return /* record */[
                      /* status : FastForwarding */3,
                      /* currentTime */state[/* currentTime */1],
                      /* activeTrackIndex */state[/* activeTrackIndex */2]
                    ];
            }
          }
          
        }), /* record */[
        /* status : Stopped */0,
        /* currentTime */0,
        /* activeTrackIndex */undefined
      ]);
  var send = match[1];
  var state = match[0];
  React.useEffect((function () {
          var match = playerRef.current;
          if (!(match == null)) {
            match.currentTime = state[/* currentTime */1];
          }
          return undefined;
        }), /* array */[state[/* currentTime */1]]);
  React.useEffect((function () {
          var match = playerRef.current;
          if (!(match == null)) {
            var match$1 = state[/* status */0];
            switch (match$1) {
              case 1 : 
                  match.play();
                  break;
              case 2 : 
                  Curry._1(send, /* Rewind */3);
                  break;
              case 3 : 
                  Curry._1(send, /* FastForward */2);
                  break;
              case 0 : 
              case 4 : 
                  match.pause();
                  break;
              
            }
          }
          return undefined;
        }), /* tuple */[
        state[/* status */0],
        state[/* currentTime */1]
      ]);
  var match$1 = state[/* activeTrackIndex */2];
  var match$2 = state[/* status */0];
  return React.createElement(React.Fragment, undefined, React.createElement(Library$ReactHooksTemplate.make, {
                  tracks: tracks,
                  playTrack: (function (i) {
                      return Curry._1(send, /* PlayTrack */[i]);
                    })
                }), React.createElement("nav", undefined, React.createElement("main", undefined, Util$ReactHooksTemplate.str(match$1 !== undefined ? "Now playing: " + Caml_array.caml_array_get(tracks, match$1)[/* name */0] : "Play a song, stupid")), React.createElement("section", {
                      "aria-label": "player"
                    }, React.createElement("audio", {
                          ref: playerRef
                        }, React.createElement("source", {
                              src: "viper.mp3",
                              type: "audio/mp3"
                            }), React.createElement("p", undefined, Util$ReactHooksTemplate.str("Your browser doesn't support HTML5 video. Here is a "), React.createElement("a", {
                                  href: "rabbit320.mp4"
                                }, Util$ReactHooksTemplate.str("link to the video ")), Util$ReactHooksTemplate.str("instead."))), React.createElement("div", {
                          className: "controls"
                        }, React.createElement("button", {
                              className: "playpause",
                              onClick: (function (param) {
                                  return Curry._1(send, /* PlayPause */0);
                                })
                            }, Util$ReactHooksTemplate.str(match$2 !== 1 ? "Play" : "Pause")), React.createElement("button", {
                              className: "stop",
                              onClick: (function (param) {
                                  return Curry._1(send, /* Stop */1);
                                })
                            }, Util$ReactHooksTemplate.str("Stop")), React.createElement("button", {
                              className: "rwd",
                              onClick: (function (param) {
                                  return Curry._1(send, /* Rewind */3);
                                })
                            }, Util$ReactHooksTemplate.str("Rwd")), React.createElement("button", {
                              className: "fwd",
                              onClick: (function (param) {
                                  return Curry._1(send, /* FastForward */2);
                                })
                            }, Util$ReactHooksTemplate.str("Fwd")), React.createElement("div", {
                              className: "time"
                            }, Util$ReactHooksTemplate.str(String(state[/* currentTime */1])))))));
}

var make = PlayerAlt;

exports.make = make;
/*  Not a pure module */