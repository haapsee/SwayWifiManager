/**
 * MIT License
 * 
 * Copyright (c) 2025 Eemil Haapsaari
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * 
 * ----------------------------------------------------------------------------
 * wifi_scanner.h
 * ----------------------------------------------------------------------------
 * This file contains the declaration of the WifiScanner class and the structs
 * used by the class.
 * 
 * The WifiScanner class is used to scan for available wifi networks using the
 * nmcli command. The class stores the networks in a vector of WifiNetwork
 * structs.
 * 
 * @author Eemil Haapsaari
 * @version 0.1
 * @date 2025-10-01
 * 
 */

#ifndef WIFI_SCANNER_H
#define WIFI_SCANNER_H

#include <vector>
#include <string>
#include <iostream>

#include "utils.h"


struct HeaderPosition {
    ulong start;
    ulong length;
};

struct HeaderPositions {
    HeaderPosition inUse;
    HeaderPosition ssid;
    HeaderPosition bssid;
    HeaderPosition mode;
    HeaderPosition channel;
    HeaderPosition signal;
    HeaderPosition security;
    HeaderPosition active;
};


struct WifiNetwork {
    bool inUse;
    std::string ssid;
    std::string bssid;
    std::string mode;
    std::string channel;
    std::string signal;
    std::string security;
    std::string active;
};


class WifiScanner {
    public:
        WifiScanner();
        void scan();
        void print() const;
    private:
        std::vector<WifiNetwork> networks;
        void parseNetworks(FILE* nmcli_output);
        WifiNetwork parseNetwork(std::string line, HeaderPositions headerPositions);
        HeaderPositions getHeaderPositions(std::string header);
        HeaderPosition getHeaderPosition(std::string header, std::string field, std::string nextField);
};

#endif