#ifndef R_CORE_CORE_H
#define R_CORE_CORE_H

#include <chrono>
#include <memory>
#include <thread>
#include <vector>
#include <atomic>
#include <string>
#include "r_core/executor.h"

namespace r_core
{
    class RendererInterface;
    class Scense;
    class RenderExecutor;
//    class LogicThread;
    class Core
    {
    public:
        Core();
        ~Core();

        bool run();
        bool pause();
        bool resume();
        void stop();

        void forward(std::chrono::milliseconds mill_sec);

    private:
//        std::shared_ptr<LogicThread> logic_thread;
        std::shared_ptr<RenderExecutor> m_render_executor;
    };

    class RenderExecutor : public Executor
    {
    public:
        RenderExecutor();
        ~RenderExecutor();

        void load_scense(std::shared_ptr<Scense> scense);

    protected:
        virtual void on_running() override;

    };

//    class LogicThread
//    {
//    public:
//        LogicThread();
//        ~LogicThread();

//    private:
//        std::shared_ptr<std::thread> m_worker;
//    };

    class InputInterface
    {

    };

    class GameLogicInterface
    {

    };

    class ScenseInterface
    {
    public:
        ScenseInterface();
        virtual ~ScenseInterface();
        virtual bool load(const std::string &path) = 0;
        virtual bool init() = 0;

        virtual void reset() = 0;
        virtual void forward(std::chrono::milliseconds mill_sec) = 0;
        virtual void back(std::chrono::milliseconds mill_sec) = 0;
        virtual void time() = 0;
    };

    class UIInterface
    {

    };
}















#endif
