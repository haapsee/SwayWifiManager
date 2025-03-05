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

#include "gtk.h"

MainWindow::MainWindow(std::vector<WifiNetwork> wifi_networks)
{
    set_title("Sway Network Manager");
    set_default_size(400, 200);
    
    Gtk::Button button("Quit");
    button.set_hexpand(true);
    button.set_halign(Gtk::Align::END);
    button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_close));

    std::vector<Glib::ustring> wifi_networks_str(wifi_networks.size());
    for (int i = 0; i < wifi_networks.size(); i++) {
        WifiNetwork network = wifi_networks[i];
        wifi_networks_str[i] = network.ssid + " (" + network.signal + ")" + 
            " \t[" + network.security + "]" + 
            " \t[" + network.mode + "]" + 
            " \t[" + network.channel + "]" + 
            " \t[" + network.active + "]" + 
            " \t[" + std::to_string(network.inUse) + "]" +
            " \t[" + std::to_string(network.is_saved) + "]";
    }

    string_list = Gtk::StringList::create(wifi_networks_str);
    auto selection_model = Gtk::SingleSelection::create(string_list);
    selection_model->set_autoselect(false);
    selection_model->set_can_unselect(true);
    
    Gtk::ListView listView;
    listView.set_model(selection_model);

    auto factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(
      sigc::mem_fun(*this, &MainWindow::on_setup_label));
    factory->signal_bind().connect(
      sigc::mem_fun(*this, &MainWindow::on_bind_name));
    listView.set_factory(factory);

    Gtk::ScrolledWindow scrolledWindow;
    scrolledWindow.set_expand(true);
    scrolledWindow.set_child(listView);

    Gtk::Box vbox(Gtk::Orientation::VERTICAL);
    vbox.append(scrolledWindow);
    vbox.append(button);
    vbox.set_margin(5);

    set_child(vbox);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    list_item->set_child(*Gtk::make_managed<Gtk::Label>("", Gtk::Align::START));
}

void MainWindow::on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
    auto pos = list_item->get_position();
    if (pos == GTK_INVALID_LIST_POSITION)
        return;
    auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
    if (!label)
        return;
    label->set_text(string_list->get_string(pos));
}

void MainWindow::on_button_close()
{
    set_visible(false);
}


GtkManager::GtkManager()
{
    this->app = Gtk::Application::create("com.example.swaynetworkmanager");
}

GtkManager::~GtkManager()
{
}

int GtkManager::createWindow(std::vector<WifiNetwork> wifi_networks)
{   
    return this->app->make_window_and_run<MainWindow>(0, nullptr, wifi_networks);
}