from .common import Benchmark, get_squares_

import numpy as np

class CustomMyList(Benchmark):
    def setup(self):
        self.a_192 = np.ones(192, dtype=np.int)
        self.c_192 = np.zeros(192, dtype=np.float64)
        
        self.a_384 = np.ones(384, dtype=np.int)
        self.c_384 = np.zeros(384, dtype=np.float64)
        
        self.a_768 = np.ones(768, dtype=np.int)
        self.c_768 = np.zeros(768, dtype=np.float64)
        
        self.a_1536 = np.ones(1536, dtype=np.int)
        self.c_1536 = np.zeros(1536, dtype=np.float64)
        
        self.a_2048 = np.ones(2048, dtype=np.int)
        self.c_2048 = np.zeros(2048, dtype=np.float64)
        
        self.a_4096 = np.ones(4096, dtype=np.int)
        self.c_4096 = np.zeros(4096, dtype=np.float64)
        
        self.a_8192 = np.ones(8192, dtype=np.int)
        self.c_8192 = np.zeros(8192, dtype=np.float64)
        
        self.a_16384 = np.ones(16384, dtype=np.int)
        self.c_16384 = np.zeros(16384, dtype=np.float64)
        
        self.a_20480 = np.ones(20480, dtype=np.int)
        self.c_20480 = np.zeros(20480, dtype=np.float64)
        
        self.a_40960 = np.ones(40960, dtype=np.int)
        self.c_40960 = np.zeros(40960, dtype=np.float64)
        
        self.a_81920 = np.ones(81920, dtype=np.int)
        self.c_81920 = np.zeros(81920, dtype=np.float64)
        
        self.a_163840 = np.ones(163840, dtype=np.int)
        self.c_163840 = np.zeros(163840, dtype=np.float64)
        
        self.a_204800 = np.ones(204800, dtype=np.int)
        self.c_204800 = np.zeros(204800, dtype=np.float64)
        
        self.a_409600 = np.ones(409600, dtype=np.int)
        self.c_409600 = np.zeros(409600, dtype=np.float64)
        
        self.a_819200 = np.ones(819200, dtype=np.int)
        self.c_819200 = np.zeros(819200, dtype=np.float64)
        
        self.a_1638400 = np.ones(1638400, dtype=np.int)
        self.c_1638400 = np.zeros(1638400, dtype=np.float64)
        
        self.a_2097152 = np.ones(2097152, dtype=np.int)
        self.c_2097152 = np.zeros(2097152, dtype=np.float64)
        
        self.a_4194304 = np.ones(4194304, dtype=np.int)
        self.c_4194304 = np.zeros(4194304, dtype=np.float64)
        
        self.a_8388608 = np.ones(8388608, dtype=np.int)
        self.c_8388608 = np.zeros(8388608, dtype=np.float64)

        self.a_16777216 = np.ones(16777216, dtype=np.int)
        self.c_16777216 = np.zeros(16777216, dtype=np.float64)

    def time_astype_to_float64_00000192(self):
        self.c_192 = self.a_192.astype(np.float64)

    def time_astype_to_float64_00000384(self):
        self.c_384 = self.a_384.astype(np.float64)

    def time_astype_to_float64_00000768(self):
        self.c_768 = self.a_768.astype(np.float64)

    def time_astype_to_float64_00001536(self):
        self.c_1536 = self.a_1536.astype(np.float64)
        
    def time_astype_to_float64_00002048(self):
        self.c_2048 = self.a_2048.astype(np.float64)

    def time_astype_to_float64_00004096(self):
        self.c_4096 = self.a_4096.astype(np.float64)

    def time_astype_to_float64_00008192(self):
        self.c_8192 = self.a_8192.astype(np.float64)

    def time_astype_to_float64_00016384(self):
        self.c_16384 = self.a_16384.astype(np.float64)

    def time_astype_to_float64_00020480(self):
        self.c_20480 = self.a_20480.astype(np.float64)

    def time_astype_to_float64_00040960(self):
        self.c_40960 = self.a_40960.astype(np.float64)

    def time_astype_to_float64_00081920(self):
        self.c_81920 = self.a_81920.astype(np.float64)

    def time_astype_to_float64_00163840(self):
        self.c_163840 = self.a_163840.astype(np.float64)

    def time_astype_to_float64_00204800(self):
        self.c_204800 = self.a_204800.astype(np.float64)

    def time_astype_to_float64_00409600(self):
        self.c_409600 = self.a_409600.astype(np.float64)

    def time_astype_to_float64_00819200(self):
        self.c_819200 = self.a_819200.astype(np.float64)

    def time_astype_to_float64_01638400(self):
        self.c_1638400 = self.a_1638400.astype(np.float64)
        
    def time_astype_to_float64_02097152(self):
        self.c_2097152 = self.a_2097152.astype(np.float64)

    def time_astype_to_float64_04194304(self):
        self.c_4194304 = self.a_4194304.astype(np.float64)

    def time_astype_to_float64_08388608(self):
        self.c_8388608 = self.a_8388608.astype(np.float64)

    def time_astype_to_float64_16777216(self):
        self.c_16777216 = self.a_16777216.astype(np.float64)

