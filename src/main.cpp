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

#include <iostream>
#include <vector>
#include "networking/networking_interface.h"
#include "networking/nmcli/nmcli.h"


int main() {
    Nmcli nmcli;
    nmcli.scanNetworks();
    std::vector<WifiNetwork> wifi_networks = nmcli.getAvailableNetworks();

    for (const auto& network : wifi_networks) {
        std::cout << "SSID: " << network.ssid << std::endl;
        std::cout << "Mode: " << network.mode << std::endl;
        std::cout << "Channel: " << network.channel << std::endl;
        std::cout << "Signal: " << network.signal << std::endl;
        std::cout << "Security: " << network.security << std::endl;
        std::cout << "Active: " << network.active << std::endl;
        std::cout << "In use: " << network.inUse << std::endl;
        std::cout << std::endl;
    }

    return 0;
}