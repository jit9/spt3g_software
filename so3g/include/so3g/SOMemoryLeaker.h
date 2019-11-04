#ifndef _G3_EXPOOL_H
#define _G3_EXPOOL_H

#include <pybindings.h>
#include <G3Module.h>

#include <vector>

class SOMemoryLeaker : public G3Module {
public:
    SOMemoryLeaker() {}
    ~SOMemoryLeaker();

    void Process(G3FramePtr frame, std::deque<G3FramePtr> &out);
    void Clear();

private:

    std::vector<G3FrameObjectConstPtr> unpacked_frames;

    SET_LOGGER("SOMemoryLeaker");
};

G3_POINTERS(SOMemoryLeaker);

#endif
