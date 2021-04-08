#include "r_core/core.h"
#include <iostream>
namespace r_core
{
    Core::Core()
    {
        m_render_executor = std::make_shared<RenderExecutor>();
        m_render_executor->set_start_callback([](){
            std::cout <<"start cb" <<std::endl;
        });

        m_render_executor->set_stop_callback([](){
            std::cout <<"stop cb" <<std::endl;
        });
    }

    Core::~Core()
    {

    }

    bool Core::run()
    {
        return m_render_executor->start();
    }

    bool Core::pause()
    {
        return m_render_executor->pause();
    }

    bool Core::resume()
    {
        return m_render_executor->resume();
    }

    void Core::stop()
    {
        return m_render_executor->stop();
    }

    RenderExecutor::RenderExecutor()
    {

    }

    RenderExecutor::~RenderExecutor()
    {

    }


//    LogicThread::LogicThread()
//    {
//        m_worker = std::make_shared<std::thread>([this]() {

//        });
//    }
}

















