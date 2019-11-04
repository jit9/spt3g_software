#ifndef _G3_EXPOOL_H
#define _G3_EXPOOL_H

#include <pybindings.h>
#include <G3Module.h>

#include <vector>

class G3MemoryLeaker : public G3Module {
public:
    G3MemoryLeaker() {}
    ~G3MemoryLeaker();

    void Process(G3FramePtr frame, std::deque<G3FramePtr> &out);
    void Clear();

private:

    std::vector<G3FrameObjectConstPtr> unpacked_frames;

    SET_LOGGER("G3MemoryLeaker");
};

G3_POINTERS(G3MemoryLeaker);

#endif
