from .common import Benchmark, get_squares_

import numpy as np

class CustomMyList(Benchmark):
    def setup(self):
        self.float64_l192 = [np.float64(i) for i in range(192)]
        self.float64_l384 = [np.float64(i) for i in range(384)]
        self.float64_l768 = [np.float64(i) for i in range(768)]
        self.float64_l1536 = [np.float64(i) for i in range(1536)]
        self.float64_l2048 = [np.float64(i) for i in range(2048)]
        self.float64_l4096 = [np.float64(i) for i in range(4096)]
        self.float64_l8192 = [np.float64(i) for i in range(8192)]
        self.float64_l16384 = [np.float64(i) for i in range(16384)]
        self.float64_l20480 = [np.float64(i) for i in range(20480)]
        self.float64_l40960 = [np.float64(i) for i in range(40960)]
        self.float64_l81920 = [np.float64(i) for i in range(81920)]
        self.float64_l163840 = [np.float64(i) for i in range(163840)]
        self.float64_l204800 = [np.float64(i) for i in range(204800)]
        self.float64_l409600 = [np.float64(i) for i in range(409600)]
        self.float64_l819200 = [np.float64(i) for i in range(819200)]
        self.float64_l1638400 = [np.float64(i) for i in range(1638400)]
        self.float64_l2097152 = [np.float64(i) for i in range(2097152)]
        self.float64_l4194304 = [np.float64(i) for i in range(4194304)]
        self.float64_l8388608 = [np.float64(i) for i in range(8388608)]
        self.float64_l16777216 = [np.float64(i) for i in range(16777216)]

    def time_array_float64_00000192(self):
        np.array(self.float64_l192)

    def time_array_float64_00000384(self):
        np.array(self.float64_l384)

    def time_array_float64_00000768(self):
        np.array(self.float64_l768)

    def time_array_float64_00001536(self):
        np.array(self.float64_l1536)
        
    def time_array_float64_00002048(self):
        np.array(self.float64_l2048)

    def time_array_float64_00004096(self):
        np.array(self.float64_l4096)

    def time_array_float64_00008192(self):
        np.array(self.float64_l8192)

    def time_array_float64_00016384(self):
        np.array(self.float64_l16384)

    def time_array_float64_00020480(self):
        np.array(self.float64_l20480)

    def time_array_float64_00040960(self):
        np.array(self.float64_l40960)

    def time_array_float64_00081920(self):
        np.array(self.float64_l81920)

    def time_array_float64_00163840(self):
        np.array(self.float64_l163840)

    def time_array_float64_00204800(self):
        np.array(self.float64_l204800)

    def time_array_float64_00409600(self):
        np.array(self.float64_l409600)

    def time_array_float64_00819200(self):
        np.array(self.float64_l819200)

    def time_array_float64_01638400(self):
        np.array(self.float64_l1638400)

    def time_array_float64_02097152(self):
        np.array(self.float64_l2097152)

    def time_array_float64_04194304(self):
        np.array(self.float64_l4194304)

    def time_array_float64_08388608(self):
        np.array(self.float64_l8388608)

    def time_array_float64_16777216(self):
        np.array(self.float64_l16777216)
