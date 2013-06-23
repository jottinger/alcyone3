#ifndef __WEBSERVICE_H__
#define __WEBSERVICE_H__ 1
/*
    Copyright 2012- by Joseph B. Ottinger.

    This file is part of Alcyone.

    Alcyone is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Alcyone is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Alcyone.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "pedal.h"
#include "midi.h"
#include <onion/onion.hpp>
#include <onion/response.hpp>
#include <onion/request.hpp>


enum ALCYONE_MESSAGE {
    MSG_MIDI_RESET=0x10,
    MSG_MIDI_CHANNEL_CHANGE=0x20,
    MSG_REQUEST_STATUS=0x30,
    MSG_MIDI_OCTAVE_CHANGE=0x40,
    MSG_MIDI_TRANSPOSITION_CHANGE=0x80,
    MSG_RESET=0xf0
};

class AlcyoneService {
private:
protected:
    MIDI* midi;
    Pedal **pedals;
public:
    AlcyoneService(MIDI* _midi, Pedal **_pedals) {
        midi=_midi;
        pedals=_pedals;
    }
    onion_connection_status root(Onion::Request &req, Onion::Response& res);
    onion_connection_status pedal(Onion::Request &req, Onion::Response& res);
    onion_connection_status nullResponse(Onion::Request &req, Onion::Response& res);
};

/*
class WebService {
private:
protected:
    MIDI* midi;
    Pedal **pedals;
public:
    WebService(MIDI* _midi, Pedal **_pedals) {
        midi=_midi;
        pedals=_pedals;
    }
    void handleRoot(void *p, onion_request* req, onion_response* res);
    void handlePedal(void *p, onion_request* req, onion_response* res);
};
*/
#endif
