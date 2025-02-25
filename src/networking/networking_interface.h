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

#ifndef NETWORKING_INTERFACE_H
#define NETWORKING_INTERFACE_H


#include <string>
#include <vector>


struct WifiNetwork {
    bool inUse;
    std::string ssid;
    std::string mode;
    std::string channel;
    std::string signal;
    std::string security;
    std::string active;
    bool is_saved;
};


class NetworkingInterface {
public:

    virtual std::vector<WifiNetwork> getAvailableNetworks() const = 0;
    // virtual std::vector<WifiNetwork> getSavedNetworks() const = 0;
    virtual bool createConnection(const std::string& ssid, const std::string& password) = 0;
    virtual bool updateConnection(const std::string& ssid, const std::string& password) = 0;
    virtual bool deleteConnection(const std::string& ssid) = 0;
    virtual bool activateConnection(const std::string& ssid) = 0;
    virtual bool deactivateConnection(const std::string& ssid) = 0;
    virtual std::string getStatus() const = 0;
    virtual std::string getCurrentConnection() const = 0;
    virtual bool scanNetworks() = 0;
};

#endif