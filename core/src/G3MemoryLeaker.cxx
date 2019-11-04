#include <pybindings.h>
#include <iostream>
#include <G3MemoryLeaker.h>

/* For the pipeline test function. */
#include <G3Pipeline.h>
#include <G3Reader.h>

G3MemoryLeaker::~G3MemoryLeaker()
{
    std::cout << "G3MemoryLeaker destructor.\n";
}

void G3MemoryLeaker::Process(G3FramePtr frame, std::deque<G3FramePtr> &out)
{
    out.push_back(frame);
    if (frame->type == G3Frame::EndProcessing)
        return;

    unpacked_frames.push_back(frame->operator[]("signal"));
}

void G3MemoryLeaker::Clear()
{
    unpacked_frames.clear();
}

static
void run_memory_leaker(std::string filename)
{
    // Local scope to force cleanup of pool, pipeline.
    {
        auto *pool = new G3MemoryLeaker();
        auto pool_p = G3ModulePtr(pool);

        std::cout << "Running the pipeline...\n";
        G3Pipeline pipe;
        pipe.Add(G3ModulePtr(new G3Reader(filename)));
        pipe.Add(pool_p);
        pipe.Run();

        std::cout << "Pause for 5 sec with frames held in pool object...\n";
        usleep(5000000);

        std::cout << "Clean up..." << std::endl;
        pool->Clear();
    }

    std::cout << "Pause in would-be cleaned up state." << std::endl;
    usleep(10000000);
}


EXPORT_G3MODULE_AND("core", G3MemoryLeaker,
                    (init<>()),
                    "Docstring.",
                    .def("Clear", &G3MemoryLeaker::Clear)
    );

PYBINDINGS("core") {
    using namespace boost::python;

    def("run_memory_leaker", &run_memory_leaker, "run the leak test... give a filename.");
    }


