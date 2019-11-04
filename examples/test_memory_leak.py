from spt3g import core
import os, sys

test_file = './test.g3'


if not os.path.exists(test_file):
    import numpy as np

    file_size = 2e9
    ndet = 2
    nframe = 100
    nsamp = int(file_size / ndet / nframe / 8)
    data_type = 'tmap'   # t, d, tmap

    print('File size %.1f MB split over %i dets.' % (file_size/1e6, ndet))
    print('Writing %i samples per det per frame.' % nsamp)
    print('Your object will at key "signal".')
    w = core.G3Writer(test_file)
    for i in range(nframe):
        f = core.G3Frame(core.G3FrameType.Scan)
        if data_type == 'tmap':
            f['signal'] = core.G3TimestreamMap()
        for d in range(ndet):
            if data_type in ['tmap', 't']:
                ts = core.G3Timestream(np.arange(1.*nsamp))
            else:
                ts = core.G3VectorDouble(np.arange(1.*nsamp))
            if data_type == 'tmap':
                f['signal']['d%05i' % d] = ts
            if data_type in ['t', 'd']:
                if d == 0:
                    f['signal'] = ts
                else:
                    f['signal_d%05i' % d] = ts
        w.Process(f)

#
# The tests.
#
mode = sys.argv[1] #   test1 or test2

if mode == 'test1':

    core.run_memory_leaker(test_file)

elif mode == 'test2':

    from spt3g import core
    import sys, time

    def isolator_function():
        print("reading...")
        pipe = core.G3Pipeline()
        pipe.Add(core.G3Reader(test_file))
        #pipe.Add(so3g.SOMemoryLeaker())
        pipe.Add(core.G3MemoryLeaker())
        pipe.Run()
        print('Pausing with pipe still extant...')
        time.sleep(5)
        del pipe

    isolator_function()
    print('Pause in would-be cleaned-up state.')
    time.sleep(5)
