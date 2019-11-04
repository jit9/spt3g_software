#include <core/G3.h>
#include <core/G3Pipeline.h>
#include <core/G3Reader.h>
#include <core/G3MemoryLeaker.h>
#include <unistd.h>

int
main(int argc, const char **argv)
{
	if (argc < 2) {
		std::cerr << "Too few arguments!" << std::endl;
		return 1;
	}

        if (true) {
            G3Pipeline pipe;
            auto *pool = new G3MemoryLeaker();
            auto pool_p = G3ModulePtr(pool);

            pipe.Add(G3ModulePtr(new G3Reader(argv[1])));
            pipe.Add(pool_p);
            pipe.Run();

            std::cout << "Pause with frames held in pool object...\n";
            usleep(5000000);
            std::cout << "Clean up..." << std::endl;
            pool->Clear();
        }

        std::cout << "Pause in would-be cleaned up state." << std::endl;
        usleep(10000000);

	return 0;
}

