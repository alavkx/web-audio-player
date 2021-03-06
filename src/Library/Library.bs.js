// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE

import * as $$Array from "bs-platform/lib/es6/array.js";
import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Util$WebAudioPlayer from "../Util.bs.js";

require("./Library.css");

function posOfArray(index, xs) {
  if (index !== 0) {
    if (index >= (xs.length - 1 | 0)) {
      return /* Last */Block.__(1, [index]);
    } else {
      return /* Middle */Block.__(0, [index]);
    }
  } else {
    return /* First */1;
  }
}

function valOfPos(p) {
  if (typeof p === "number") {
    return 0;
  } else {
    return p[0];
  }
}

function eqPos(n, p) {
  if (typeof p === "number") {
    if (p !== 0) {
      return n === 0;
    } else {
      return false;
    }
  } else {
    return p[0] === n;
  }
}

function handleKeyboardEvent(e) {
  var match = e.key;
  switch (match) {
    case "ArrowDown" : 
        return /* Next */0;
    case "ArrowUp" : 
        return /* Previous */1;
    case "Enter" : 
        return /* TriggerEffect */3;
    case "Escape" : 
        return /* Blur */2;
    default:
      return /* NoOp */4;
  }
}

function Library(Props) {
  var tracks = Props.tracks;
  var playTrack = Props.playTrack;
  var match = React.useReducer((function (state, $$event) {
          var match = state[/* status */0];
          if (typeof $$event === "number") {
            if ($$event !== 2) {
              if ($$event >= 3) {
                return state;
              } else if (typeof match === "number") {
                if (match === 0) {
                  return /* record */[/* status : First */1];
                } else if ($$event !== 0) {
                  return state;
                } else {
                  return /* record */[/* status : Middle */Block.__(0, [1])];
                }
              } else if (match.tag) {
                if ($$event !== 0) {
                  return /* record */[/* status */posOfArray(match[0] - 1 | 0, tracks)];
                } else {
                  return state;
                }
              } else {
                var i = match[0];
                if ($$event !== 0) {
                  return /* record */[/* status */posOfArray(i - 1 | 0, tracks)];
                } else {
                  return /* record */[/* status */posOfArray(i + 1 | 0, tracks)];
                }
              }
            } else {
              return /* record */[/* status : None */0];
            }
          } else {
            return /* record */[/* status */posOfArray($$event[0], tracks)];
          }
        }), /* record */[/* status : None */0]);
  var send = match[1];
  var state = match[0];
  return React.createElement("table", {
              className: "library",
              tabIndex: 0,
              onKeyDown: (function (e) {
                  var x = handleKeyboardEvent(e);
                  if (typeof x === "number" && x === 3) {
                    return Curry._1(playTrack, valOfPos(state[/* status */0]));
                  } else {
                    return Curry._1(send, x);
                  }
                }),
              onFocus: (function (_e) {
                  return Curry._1(send, /* FocusRow */[0]);
                }),
              onBlur: (function (_e) {
                  return Curry._1(send, /* Blur */2);
                })
            }, React.createElement("tbody", undefined, $$Array.mapi((function (i, param) {
                        var isFocusedRow = eqPos(i, state[/* status */0]);
                        return React.createElement("tr", {
                                    key: String(i),
                                    style: isFocusedRow ? ({
                                          borderColor: "blue"
                                        }) : { },
                                    onClick: (function (param) {
                                        return Curry._1(send, /* FocusRow */[i]);
                                      }),
                                    onDoubleClick: (function (param) {
                                        return Curry._1(playTrack, i);
                                      })
                                  }, React.createElement("td", undefined, Util$WebAudioPlayer.str(param[/* artist */1])), React.createElement("td", undefined, Util$WebAudioPlayer.str(param[/* name */0])));
                      }), tracks)));
}

var make = Library;

export {
  posOfArray ,
  valOfPos ,
  eqPos ,
  handleKeyboardEvent ,
  make ,
  
}
/*  Not a pure module */
