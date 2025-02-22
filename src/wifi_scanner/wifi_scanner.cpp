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
 */

#include "wifi_scanner.h"


WifiScanner::WifiScanner() {}

void WifiScanner::print() const {
    for (WifiNetwork network : this->networks) {
        std::cout << "IN-USE: " << network.inUse << std::endl;
        std::cout << "SSID: " << network.ssid << std::endl;
        std::cout << "BSSID: " << network.bssid << std::endl;
        std::cout << "MODE: " << network.mode << std::endl;
        std::cout << "CHAN: " << network.channel << std::endl;
        std::cout << "SIGNAL: " << network.signal << std::endl;
        std::cout << "SECURITY: " << network.security << std::endl;
        std::cout << "ACTIVE: " << network.active << std::endl;
        std::cout << std::endl;
    }
}

void WifiScanner::scan() {
    FILE *fp = popen("nmcli -f in-use,ssid,bssid,mode,chan,signal,security,active dev wifi list", "r");
    if (fp == NULL) {
        std::cerr << "Failed to run command" << std::endl;
        return;
    }
    this->parseNetworks(fp);
    pclose(fp);
}

void WifiScanner::parseNetworks(FILE* nmcli_output) {
    char line[256];

    // Get Header positions
    fgets(line, sizeof(line), nmcli_output);
    std::string header = line;
    HeaderPositions headerPositions = this->getHeaderPositions(header);

    // Parse networks
    while (fgets(line, sizeof(line), nmcli_output)) {
        std::string lineStr = line;
        WifiNetwork network = this->parseNetwork(lineStr, headerPositions);
        this->networks.push_back(network);
    }
}

WifiNetwork WifiScanner::parseNetwork(std::string line, HeaderPositions headerPositions) {
    std::string inUse = line.substr(headerPositions.inUse.start, headerPositions.inUse.length);
    std::string ssid = line.substr(headerPositions.ssid.start, headerPositions.ssid.length);
    std::string bssid = line.substr(headerPositions.bssid.start, headerPositions.bssid.length);
    std::string mode = line.substr(headerPositions.mode.start, headerPositions.mode.length);
    std::string channel = line.substr(headerPositions.channel.start, headerPositions.channel.length);
    std::string signal = line.substr(headerPositions.signal.start, headerPositions.signal.length);
    std::string security = line.substr(headerPositions.security.start, headerPositions.security.length);
    std::string active = line.substr(headerPositions.active.start, headerPositions.active.length);

    return WifiNetwork{
        utils::removeTrailingWhitespace(inUse) == "*" ? true : false,
        utils::removeTrailingWhitespace(ssid),
        utils::removeTrailingWhitespace(bssid),
        utils::removeTrailingWhitespace(mode),
        utils::removeTrailingWhitespace(channel),
        utils::removeTrailingWhitespace(signal),
        utils::removeTrailingWhitespace(security),
        utils::removeTrailingWhitespace(active)
    };
}

HeaderPositions WifiScanner::getHeaderPositions(std::string header) {
    HeaderPositions headerPositions = {
        this->getHeaderPosition(header, "IN-USE", "SSID"),
        this->getHeaderPosition(header, "SSID", "BSSID"),
        this->getHeaderPosition(header, "BSSID", "MODE"),
        this->getHeaderPosition(header, "MODE", "CHAN"),
        this->getHeaderPosition(header, "CHAN", "SIGNAL"),
        this->getHeaderPosition(header, "SIGNAL", "SECURITY"),
        this->getHeaderPosition(header, "SECURITY", "ACTIVE"),
        this->getHeaderPosition(header, "ACTIVE", "")
    };
    return headerPositions;
}

HeaderPosition WifiScanner::getHeaderPosition(
    std::string header, std::string field, std::string nextField
) {
    ulong start = header.find(field);
    bool hasNext = nextField != "";
    ulong length = hasNext ? header.find(nextField) - start : header.length() - start;
    HeaderPosition headerPosition = {start, length};
    return headerPosition;
}