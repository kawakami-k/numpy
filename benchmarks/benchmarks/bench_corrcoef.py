from .common import Benchmark, get_squares_

import numpy as np

class CustomMyList(Benchmark):
    def setup(self):
        np.random.seed(seed=32)
        self.a_96 = np.random.rand(96)
        self.a_192 = np.random.rand(192)
        self.a_384 = np.random.rand(384)
        self.a_768 = np.random.rand(768)
        self.a_1024 = np.random.rand(1024)
        self.a_2048 = np.random.rand(2048)
        self.a_4096 = np.random.rand(4096)
        self.a_8192 = np.random.rand(8192)
        self.a_10240 = np.random.rand(10240)
        self.a_20480 = np.random.rand(20480)
        self.a_40960 = np.random.rand(40960)
        self.a_81920 = np.random.rand(81920)
        self.a_102400 = np.random.rand(102400)
        self.a_204800 = np.random.rand(204800)
        self.a_409600 = np.random.rand(409600)
        self.a_819200 = np.random.rand(819200)
        self.a_1048576 = np.random.rand(1048576)
        self.a_2097152 = np.random.rand(2097152)
        self.a_4194304 = np.random.rand(4194304)
        self.a_8388608 = np.random.rand(8388608)

        np.random.seed(seed=64)
        self.b_96 = np.random.rand(96)
        self.b_192 = np.random.rand(192)
        self.b_384 = np.random.rand(384)
        self.b_768 = np.random.rand(768)
        self.b_1024 = np.random.rand(1024)
        self.b_2048 = np.random.rand(2048)
        self.b_4096 = np.random.rand(4096)
        self.b_8192 = np.random.rand(8192)
        self.b_10240 = np.random.rand(10240)
        self.b_20480 = np.random.rand(20480)
        self.b_40960 = np.random.rand(40960)
        self.b_81920 = np.random.rand(81920)
        self.b_102400 = np.random.rand(102400)
        self.b_204800 = np.random.rand(204800)
        self.b_409600 = np.random.rand(409600)
        self.b_819200 = np.random.rand(819200)
        self.b_1048576 = np.random.rand(1048576)
        self.b_2097152 = np.random.rand(2097152)
        self.b_4194304 = np.random.rand(4194304)
        self.b_8388608 = np.random.rand(8388608)
        
        self.c_96 = np.zeros((2,2), dtype=np.float64)
        self.c_192 = np.zeros((2,2), dtype=np.float64)
        self.c_384 = np.zeros((2,2), dtype=np.float64)
        self.c_768 = np.zeros((2,2), dtype=np.float64)
        self.c_1024 = np.zeros((2,2), dtype=np.float64)
        self.c_2048 = np.zeros((2,2), dtype=np.float64)
        self.c_4096 = np.zeros((2,2), dtype=np.float64)
        self.c_8192 = np.zeros((2,2), dtype=np.float64)
        self.c_10240 = np.zeros((2,2), dtype=np.float64)
        self.c_20480 = np.zeros((2,2), dtype=np.float64)
        self.c_40960 = np.zeros((2,2), dtype=np.float64)
        self.c_81920 = np.zeros((2,2), dtype=np.float64)
        self.c_102400 = np.zeros((2,2), dtype=np.float64)
        self.c_204800 = np.zeros((2,2), dtype=np.float64)
        self.c_409600 = np.zeros((2,2), dtype=np.float64)
        self.c_819200 = np.zeros((2,2), dtype=np.float64)
        self.c_1048576 = np.zeros((2,2), dtype=np.float64)
        self.c_2097152 = np.zeros((2,2), dtype=np.float64)        
        self.c_4194304 = np.zeros((2,2), dtype=np.float64)
        self.c_8388608 = np.zeros((2,2), dtype=np.float64)

    def time_corrcoef_0000096(self):
        self.c_96 = np.corrcoef(self.a_96, self.b_96)

    def time_corrcoef_0000192(self):
        self.c_192 = np.corrcoef(self.a_192, self.b_192)

    def time_corrcoef_0000384(self):
        self.c_384 = np.corrcoef(self.a_384, self.b_384)

    def time_corrcoef_0000768(self):
        self.c_768 = np.corrcoef(self.a_768, self.b_768)

    def time_corrcoef_0001024(self):
        self.c_1024 = np.corrcoef(self.a_1024, self.b_1024)

    def time_corrcoef_0002048(self):
        self.c_2048 = np.corrcoef(self.a_2048, self.b_2048)

    def time_corrcoef_0004096(self):
        self.c_4096 = np.corrcoef(self.a_4096, self.b_4096)

    def time_corrcoef_0008192(self):
        self.c_8192 = np.corrcoef(self.a_8192, self.b_8192)

    def time_corrcoef_0010240(self):
        self.c_10240 = np.corrcoef(self.a_10240, self.b_10240)

    def time_corrcoef_0020480(self):
        self.c_20480 = np.corrcoef(self.a_20480, self.b_20480)

    def time_corrcoef_0040960(self):
        self.c_40960 = np.corrcoef(self.a_40960, self.b_40960)

    def time_corrcoef_0081920(self):
        self.c_81920 = np.corrcoef(self.a_81920, self.b_81920)

    def time_corrcoef_0102400(self):
        self.c_102400 = np.corrcoef(self.a_102400, self.b_102400)

    def time_corrcoef_0204800(self):
        self.c_204800 = np.corrcoef(self.a_204800, self.b_204800)

    def time_corrcoef_0409600(self):
        self.c_409600 = np.corrcoef(self.a_409600, self.b_409600)

    def time_corrcoef_0819200(self):
        self.c_819200 = np.corrcoef(self.a_819200, self.b_819200)

    def time_corrcoef_1048576(self):
        self.c_1048576 = np.corrcoef(self.a_1048576, self.b_1048576)

    def time_corrcoef_2097152(self):
        self.c_2097152 = np.corrcoef(self.a_2097152, self.b_2097152)

    def time_corrcoef_4194304(self):
        self.c_4194304 = np.corrcoef(self.a_4194304, self.b_4194304)

    def time_corrcoef_8388608(self):
        self.c_8388608 = np.corrcoef(self.a_8388608, self.b_8388608)
