#include "r_core/executor.h"

#define call_cb(callback)           \
do {                                \
    if (callback)                   \
    {                               \
        callback();                 \
    }                               \
} while(0);

namespace r_core
{

Executor::Executor()
{

}

Executor::~Executor()
{

}

bool Executor::start()
{
    if (m_status != Status::STOP)
    {
        return false;
    }

    if (m_worker && m_worker->joinable())
    {
        m_worker->join();
    }
    m_worker.reset();

    m_worker = std::make_shared<std::thread>([this]() {
        m_status = Status::RUNNING;
        call_cb(m_start_cb);

        while (true)
        {
            if (this->m_status == Status::PAUSE)
            {
                on_pause();
                call_cb(m_pause_cb);

                while (m_status == Status::PAUSE)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }

                on_resume();
                call_cb(m_resume_cb);
            }
            if (this->m_status == Status::STOP)
            {
                on_stop();
                call_cb(m_stop_cb);

                return;
            }

            on_running();
        }
    });
    return true;
}

bool Executor::pause()
{
    if (m_status == Status::STOP)
    {
        return false;
    }

    m_status = Status::PAUSE;
    return true;
}

bool Executor::resume()
{
    if (m_status != Status::PAUSE)
    {
        return false;
    }

    m_status = Status::RUNNING;
    return true;
}

void Executor::stop()
{
    m_status = Status::STOP;
}

void Executor::set_start_callback(std::function<void(void)> cb)
{
    m_start_cb = cb;
}

void Executor::set_pause_callback(std::function<void(void)> cb)
{
    m_pause_cb = cb;
}

void Executor::set_stop_callback(std::function<void(void)> cb)
{
    m_stop_cb = cb;
}

}













