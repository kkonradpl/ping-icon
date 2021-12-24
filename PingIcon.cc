#include <glibmm/main.h>
#include <glibmm/spawn.h>
#include <thread>
#include "PingIcon.h"

PingIcon::PingIcon(const Glib::ustring &icon_reachable,
                   const Glib::ustring &icon_unreachable,
                   const Glib::ustring &hostname,
                   int                  interval,
                   int                  timeout)
{
    dispatcher.connect(sigc::mem_fun(*this, &PingIcon::dispatch));

    this->icon_reachable = icon_reachable;
    this->icon_unreachable = icon_unreachable;
    this->hostname = hostname;
    this->interval = interval;
    this->timeout = timeout;

    this->state_icon = -1;
    this->state_thread = -1;
    new std::thread(&PingIcon::loop, this);
}

void
PingIcon::notify(bool state)
{
    this->state_thread = state;
    dispatcher.emit();
}

void
PingIcon::dispatch()
{
    gboolean new_state = state_thread;

    if(this->state_icon == new_state)
        return;

    if(new_state)
    {
        if(this->icon_reachable.empty())
            this->set_visible(false);
        else
        {
            this->set(this->icon_reachable);
            this->set_visible(true);
        }
    }
    else
    {
        if(this->icon_unreachable.empty())
            this->set_visible(false);
        else
        {
            this->set(this->icon_unreachable);
            this->set_visible(true);
        }
    }

    this->state_icon = new_state;
}

void
PingIcon::loop()
{
    gint64 ts;
    int delay;
    int ret;

    Glib::SpawnFlags flags = Glib::SpawnFlags::SPAWN_DEFAULT |
                             Glib::SpawnFlags::SPAWN_SEARCH_PATH |
                             Glib::SpawnFlags::SPAWN_STDOUT_TO_DEV_NULL |
                             Glib::SpawnFlags::SPAWN_STDERR_TO_DEV_NULL;

    std::vector <std::string> args;
    args.push_back("ping");
    args.push_back("-c");
    args.push_back("1");
    args.push_back("-w");
    args.push_back(std::to_string(this->timeout));
    args.push_back(this->hostname);

    while(true)
    {
        ret = -1;
        ts = g_get_real_time();
        try
        {
            Glib::spawn_sync("",
                             args,
                             flags,
                             {},
                             nullptr,
                             nullptr,
                             &ret);
        }
        catch (Glib::Error& exception)
        {
            g_warning("%s", exception.what().c_str());
        }

        this->notify(ret == 0);

        delay = this->interval - (g_get_real_time() - ts) / 1000000;
        if(delay > 0)
            sleep(delay);
    }
}