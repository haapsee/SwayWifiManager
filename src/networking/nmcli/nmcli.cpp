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

#include "nmcli.h"
#include <cstdlib>
#include <sstream>
#include <iostream>




std::vector<WifiNetwork> Nmcli::getAvailableNetworks() const {
    std::vector<WifiNetwork> networks;

    FILE* pipe = popen("nmcli -t -f IN-USE,SSID,MODE,CHAN,SIGNAL,SECURITY,ACTIVE dev wifi", "r");
    if (!pipe) {
        std::cerr << "Failed to run nmcli command" << std::endl;
        return networks;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        std::string ss(buffer);
        WifiNetwork network;
        network.inUse = utils::removeTrailingWhitespace(ss.substr(0, ss.find(':'))) == "*" ? true : false;
        ss.erase(0, ss.find(':') + 1);
        network.ssid = utils::removeTrailingWhitespace(ss.substr(0, ss.find(':')));
        ss.erase(0, ss.find(':') + 1);
        network.mode = utils::removeTrailingWhitespace(ss.substr(0, ss.find(':')));
        ss.erase(0, ss.find(':') + 1);
        network.channel = utils::removeTrailingWhitespace(ss.substr(0, ss.find(':')));
        ss.erase(0, ss.find(':') + 1);
        network.signal = utils::removeTrailingWhitespace(ss.substr(0, ss.find(':')));
        ss.erase(0, ss.find(':') + 1);
        network.security = utils::removeTrailingWhitespace(ss.substr(0, ss.find(':')));
        ss.erase(0, ss.find(':') + 1);
        network.active = utils::removeTrailingWhitespace(ss.substr(0, ss.find(':')));
        networks.push_back(network);
    }

    pclose(pipe);
    return networks;
}

bool Nmcli::createConnection(const std::string& ssid, const std::string& password) {
    std::string command = "nmcli dev wifi connect '" + ssid + "' password '" + password + "'";
    return system(command.c_str()) == 0;
}

bool Nmcli::updateConnection(const std::string& ssid, const std::string& password) {
    // Assuming update means reconnecting with new credentials
    return createConnection(ssid, password);
}

bool Nmcli::deleteConnection(const std::string& ssid) {
    std::string command = "nmcli connection delete id '" + ssid + "'";
    return system(command.c_str()) == 0;
}

bool Nmcli::activateConnection(const std::string& ssid) {
    std::string command = "nmcli connection up id '" + ssid + "'";
    return system(command.c_str()) == 0;
}

bool Nmcli::deactivateConnection(const std::string& ssid) {
    std::string command = "nmcli connection down id '" + ssid + "'";
    return system(command.c_str()) == 0;
}

std::string Nmcli::getStatus() const {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen("nmcli general status", "r");
    if (!pipe) {
        std::cerr << "Failed to run nmcli command" << std::endl;
        return result;
    }

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);
    return result;
}

std::string Nmcli::getCurrentConnection() const {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen("nmcli -t -f NAME connection show --active", "r");
    if (!pipe) {
        std::cerr << "Failed to run nmcli command" << std::endl;
        return result;
    }

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);
    return result;
}

bool Nmcli::scanNetworks() {
    return system("nmcli dev wifi rescan") == 0;
}