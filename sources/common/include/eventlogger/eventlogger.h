/*
 *  Copyright (c) 2021,
 *  Gennaro Gallo (https://github.com/ggenny/crtmpserver)
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

#pragma once

class DLLEXP EventLogger {
public:
	EventLogger();
        
        void LogCarrierCreated(Variant &stats);
        void LogCarrierClosed(Variant &stats);        
        
        static EventLogger* GetDefaultLogger();
        
private:        
        static EventLogger* _instance;
};