#ifndef R_CORE_EXECUTOR_H
#define R_CORE_EXECUTOR_H

#include <memory>
#include <thread>
#include <atomic>
#include <functional>
#include <condition_variable>
#include <iostream>

namespace r_core
{

class Executor
{
public:
    Executor();
    virtual ~Executor();

    bool start();
    bool pause();
    bool resume();
    void stop();

    void set_start_callback(std::function<void(void)> cb);
    void set_pause_callback(std::function<void(void)> cb);
    void set_resume_callback(std::function<void(void)> cb);
    void set_stop_callback(std::function<void(void)> cb);

protected:
    virtual void on_pause() {std::cout << "on_pause" <<std::endl;}
    virtual void on_resume() {std::cout << "on_resume" << std::endl; }
    virtual void on_stop() {std::cout <<"on_stop" <<std::endl;}
    virtual void on_running() {/*std::cout << "on_running" <<std::endl;*/}

private:
    std::shared_ptr<std::thread> m_worker;
    enum class Status : int
    {
        STOP = 0,
        RUNNING,
        PAUSE,
    };
    std::atomic<Status> m_status {Status::STOP};

    std::function<void(void)> m_start_cb;
    std::function<void(void)> m_pause_cb;
    std::function<void(void)> m_resume_cb;
    std::function<void(void)> m_stop_cb;

    std::mutex m_mutex;
    std::condition_variable m_pause_cv;
};

}














#endif
