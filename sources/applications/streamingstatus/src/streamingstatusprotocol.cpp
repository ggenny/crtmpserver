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

#include "common.h"
#include "streamingstatusprotocol.h"
#include "localdefines.h"
#include "protocols/http/inboundhttpprotocol.h"
#include "application/baseclientapplication.h"
#include "application/clientapplicationmanager.h"
#include "protocols/protocolmanager.h"
#include "streaming/basestream.h"
#include "streaming/streamsmanager.h"
#include "picojson.h"
using namespace app_streamingstatus;

StreamingStatusProtocol::StreamingStatusProtocol()
: BaseProtocol(PT_STREAMING_STATUS_PROTOCOL) {

}

StreamingStatusProtocol::~StreamingStatusProtocol() {
}

bool StreamingStatusProtocol::Initialize(Variant &parameters) {
    //save the parameters
    GetCustomParameters() = parameters;
    return true;
}

IOBuffer * StreamingStatusProtocol::GetOutputBuffer() {
    //This function should return the buffer
    //ready to be transmitted over the wire or
    //NULL if no data needs to be transmitted
    //Also, there is NO guarantee that after
    //a I/O operation ALL the data is consumed
    //The I/O layer will try to send as many data as possible from this buffer
    //and adjust it afterwards. Rule of thumb: after writing into this buffer,
    //you should forget about it and NEVER try to modify data inside it. You
    //are only permitted to append data to it
    if (GETAVAILABLEBYTESCOUNT(_outputBuffer) != 0)
        return &_outputBuffer;
    return NULL;
}

bool StreamingStatusProtocol::AllowFarProtocol(uint64_t type) {
    //we only allow tcp and inbound HTTP for the
    //far protocol
    return (type == PT_TCP) || (type == PT_INBOUND_HTTP);
}

bool StreamingStatusProtocol::AllowNearProtocol(uint64_t type) {
    //this is an endpoint protocol so we don't accept
    //anything on top of it
    return false;
}

bool StreamingStatusProtocol::SignalInputData(int32_t recvAmount) {
    //this protocol doesn't have a carrier attached directly so
    //we will never operate on file descriptors
    ASSERT("Operation not supported");
    return false;
}

bool StreamingStatusProtocol::SignalInputData(IOBuffer &buffer) {

    InboundHTTPProtocol *pHTTP = (InboundHTTPProtocol *) GetFarProtocol();
    if (!pHTTP->TransferCompleted()) {
        FINEST("HTTP transfer not completed yet");
        return true;
    }

    std::string jsonString = GetStreamingStatusJSON();
    _outputBuffer.ReadFromString(jsonString);

    FINEST("HTTP request:\n%s", STR(pHTTP->GetHeaders().ToString()));

    buffer.IgnoreAll();

    pHTTP->SetOutboundHeader(HTTP_HEADERS_CONTENT_TYPE, "applicaton/json");

    return EnqueueForOutbound();
}

std::string StreamingStatusProtocol::GetStreamingStatusJSON()
{
    picojson::array streamingList;
    map<uint32_t, BaseClientApplication *> applications = ClientApplicationManager::GetAllApplications();
    FOR_MAP(applications, uint32_t, BaseClientApplication *, i) {
        FINEST("application: %s", STR(MAP_VAL(i)->GetName()));
        map<uint32_t, BaseStream *> streams = MAP_VAL(i)->GetStreamsManager()->GetAllStreams();
        FOR_MAP(streams, uint32_t, BaseStream *, j) {
            Variant sv;
            BaseStream *s = MAP_VAL(j);
            BaseProtocol *p = s->GetProtocol();
            s->GetStats(sv);
            DEBUG("%s", STR(sv.ToString()));

            picojson::object info;
            info.insert(std::make_pair("name", picojson::value(s->GetName())));
            info.insert(std::make_pair("protocol", picojson::value(tagToString(p->GetType()))));
            info.insert(std::make_pair("type", picojson::value((std::string)sv["type"])));
            info.insert(std::make_pair("upTime", picojson::value((double)sv["upTime"])));
            info.insert(std::make_pair("creationTimestamp", picojson::value((double)sv["creationTimestamp"])));
            streamingList.push_back(picojson::value(info));
        }
    }
    picojson::object jsonObject;
    jsonObject.insert(std::make_pair("streamings", picojson::value(streamingList)));
    std::string jsonString = picojson::value(jsonObject).serialize();
    FINEST("%s", jsonString.c_str());

    return jsonString;
}
