/*
 *  Copyright (c) 2010,
 *  Gavriloaie Eugen-Andrei (shiretu@gmail.com)
 *
 *  This file is part of crtmpserver.
 *  crtmpserver is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  crtmpserver is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with crtmpserver.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "streamingstatusapplication.h"
#include "protocols/baseprotocol.h"
#include "protocolfactory.h"
#include "protocols/protocolfactorymanager.h"
#include "localdefines.h"
#include "streamingstatusprotocolhandler.h"

using namespace app_streamingstatus;

StreamingStatusApplication::StreamingStatusApplication(Variant &configuration)
: BaseClientApplication(configuration) {
    _pSSHandler=NULL;
}

StreamingStatusApplication::~StreamingStatusApplication() {
    UnRegisterAppProtocolHandler(PT_STREAMING_STATUS_PROTOCOL);
    if(_pSSHandler!=NULL) {
        delete _pSSHandler;
        _pSSHandler=NULL;
    }
}

bool StreamingStatusApplication::Initialize() {
    //TODO: Add your app init code here
    //Things like parsing custom sections inside _configuration for example,
    //initialize the protocol handler(s)

    //1. Initialize the protocol handler(s)
    _pSSHandler = new StreamingStatusProtocolHandler(_configuration);
    RegisterAppProtocolHandler(PT_STREAMING_STATUS_PROTOCOL, _pSSHandler);

    //2. Use your custom values inside your app config node
    //I'll just print the config for now... Watch the logs
    FINEST("%s app config node:\n%s",
            STR(GetName()), STR(_configuration.ToString()));
    return true;
}

