from .common import Benchmark, get_squares_

import numpy as np

class CustomMyList(Benchmark):
    def setup(self):
        self.a_96 = np.ones(96, dtype=np.float64)
        self.b_96 = np.ones(96, dtype=np.float64)
        self.c_96 = np.zeros(96, dtype=np.float64)
        
        self.a_192 = np.ones(192, dtype=np.float64)
        self.b_192 = np.ones(192, dtype=np.float64)
        self.c_192 = np.zeros(192, dtype=np.float64)
        
        self.a_384 = np.ones(384, dtype=np.float64)
        self.b_384 = np.ones(384, dtype=np.float64)
        self.c_384 = np.zeros(384, dtype=np.float64)
        
        self.a_768 = np.ones(768, dtype=np.float64)
        self.b_768 = np.ones(768, dtype=np.float64)
        self.c_768 = np.zeros(768, dtype=np.float64)
        
        self.a_1024 = np.ones(1024, dtype=np.float64)
        self.b_1024 = np.ones(1024, dtype=np.float64)
        self.c_1024 = np.zeros(1024, dtype=np.float64)
        
        self.a_2048 = np.ones(2048, dtype=np.float64)
        self.b_2048 = np.ones(2048, dtype=np.float64)
        self.c_2048 = np.zeros(2048, dtype=np.float64)
        
        self.a_4096 = np.ones(4096, dtype=np.float64)
        self.b_4096 = np.ones(4096, dtype=np.float64)
        self.c_4096 = np.zeros(4096, dtype=np.float64)
        
        self.a_8192 = np.ones(8192, dtype=np.float64)
        self.b_8192 = np.ones(8192, dtype=np.float64)
        self.c_8192 = np.zeros(8192, dtype=np.float64)
        
        self.a_10240 = np.ones(10240, dtype=np.float64)
        self.b_10240 = np.ones(10240, dtype=np.float64)
        self.c_10240 = np.zeros(10240, dtype=np.float64)
        
        self.a_20480 = np.ones(20480, dtype=np.float64)
        self.b_20480 = np.ones(20480, dtype=np.float64)
        self.c_20480 = np.zeros(20480, dtype=np.float64)
        
        self.a_40960 = np.ones(40960, dtype=np.float64)
        self.b_40960 = np.ones(40960, dtype=np.float64)
        self.c_40960 = np.zeros(40960, dtype=np.float64)
        
        self.a_81920 = np.ones(81920, dtype=np.float64)
        self.b_81920 = np.ones(81920, dtype=np.float64)
        self.c_81920 = np.zeros(81920, dtype=np.float64)
        
        self.a_102400 = np.ones(102400, dtype=np.float64)
        self.b_102400 = np.ones(102400, dtype=np.float64)
        self.c_102400 = np.zeros(102400, dtype=np.float64)
        
        self.a_204800 = np.ones(204800, dtype=np.float64)
        self.b_204800 = np.ones(204800, dtype=np.float64)
        self.c_204800 = np.zeros(204800, dtype=np.float64)
        
        self.a_409600 = np.ones(409600, dtype=np.float64)
        self.b_409600 = np.ones(409600, dtype=np.float64)
        self.c_409600 = np.zeros(409600, dtype=np.float64)
        
        self.a_819200 = np.ones(819200, dtype=np.float64)
        self.b_819200 = np.ones(819200, dtype=np.float64)
        self.c_819200 = np.zeros(819200, dtype=np.float64)
        
        self.a_1048576 = np.ones(1048576, dtype=np.float64)
        self.b_1048576 = np.ones(1048576, dtype=np.float64)
        self.c_1048576 = np.zeros(1048576, dtype=np.float64)
        
        self.a_2097152 = np.ones(2097152, dtype=np.float64)
        self.b_2097152 = np.ones(2097152, dtype=np.float64)
        self.c_2097152 = np.zeros(2097152, dtype=np.float64)
        
        self.a_4194304 = np.ones(4194304, dtype=np.float64)
        self.b_4194304 = np.ones(4194304, dtype=np.float64)
        self.c_4194304 = np.zeros(4194304, dtype=np.float64)
        
        self.a_8388608 = np.ones(8388608, dtype=np.float64)
        self.b_8388608 = np.ones(8388608, dtype=np.float64)
        self.c_8388608 = np.zeros(8388608, dtype=np.float64)

    def time_double_add_0000096(self):
        np.add(self.a_96, self.b_96, out=self.c_96)

    def time_double_add_0000192(self):
        np.add(self.a_192, self.b_192, out=self.c_192)

    def time_double_add_0000384(self):
        np.add(self.a_384, self.b_384, out=self.c_384)

    def time_double_add_0000768(self):
        np.add(self.a_768, self.b_768, out=self.c_768)

    def time_double_add_0001024(self):
        np.add(self.a_1024, self.b_1024, out=self.c_1024)

    def time_double_add_0002048(self):
        np.add(self.a_2048, self.b_2048, out=self.c_2048)

    def time_double_add_0004096(self):
        np.add(self.a_4096, self.b_4096, out=self.c_4096)

    def time_double_add_0008192(self):
        np.add(self.a_8192, self.b_8192, out=self.c_8192)

    def time_double_add_0010240(self):
        np.add(self.a_10240, self.b_10240, out=self.c_10240)

    def time_double_add_0020480(self):
        np.add(self.a_20480, self.b_20480, out=self.c_20480)

    def time_double_add_0040960(self):
        np.add(self.a_40960, self.b_40960, out=self.c_40960)

    def time_double_add_0081920(self):
        np.add(self.a_81920, self.b_81920, out=self.c_81920)

    def time_double_add_0102400(self):
        np.add(self.a_102400, self.b_102400, out=self.c_102400)

    def time_double_add_0204800(self):
        np.add(self.a_204800, self.b_204800, out=self.c_204800)

    def time_double_add_0409600(self):
        np.add(self.a_409600, self.b_409600, out=self.c_409600)

    def time_double_add_0819200(self):
        np.add(self.a_819200, self.b_819200, out=self.c_819200)

    def time_double_add_1048576(self):
        np.add(self.a_1048576, self.b_1048576, out=self.c_1048576)

    def time_double_add_2097152(self):
        np.add(self.a_2097152, self.b_2097152, out=self.c_2097152)

    def time_double_add_4194304(self):
        np.add(self.a_4194304, self.b_4194304, out=self.c_4194304)

    def time_double_add_8388608(self):
        np.add(self.a_8388608, self.b_8388608, out=self.c_8388608)

    def time_double_subtract_0000096(self):
        np.subtract(self.a_96, self.b_96, out=self.c_96)

    def time_double_subtract_0000192(self):
        np.subtract(self.a_192, self.b_192, out=self.c_192)

    def time_double_subtract_0000384(self):
        np.subtract(self.a_384, self.b_384, out=self.c_384)

    def time_double_subtract_0000768(self):
        np.subtract(self.a_768, self.b_768, out=self.c_768)

    def time_double_subtract_0001024(self):
        np.subtract(self.a_1024, self.b_1024, out=self.c_1024)

    def time_double_subtract_0002048(self):
        np.subtract(self.a_2048, self.b_2048, out=self.c_2048)

    def time_double_subtract_0004096(self):
        np.subtract(self.a_4096, self.b_4096, out=self.c_4096)

    def time_double_subtract_0008192(self):
        np.subtract(self.a_8192, self.b_8192, out=self.c_8192)

    def time_double_subtract_0010240(self):
        np.subtract(self.a_10240, self.b_10240, out=self.c_10240)

    def time_double_subtract_0020480(self):
        np.subtract(self.a_20480, self.b_20480, out=self.c_20480)

    def time_double_subtract_0040960(self):
        np.subtract(self.a_40960, self.b_40960, out=self.c_40960)

    def time_double_subtract_0081920(self):
        np.subtract(self.a_81920, self.b_81920, out=self.c_81920)

    def time_double_subtract_0102400(self):
        np.subtract(self.a_102400, self.b_102400, out=self.c_102400)

    def time_double_subtract_0204800(self):
        np.subtract(self.a_204800, self.b_204800, out=self.c_204800)

    def time_double_subtract_0409600(self):
        np.subtract(self.a_409600, self.b_409600, out=self.c_409600)

    def time_double_subtract_0819200(self):
        np.subtract(self.a_819200, self.b_819200, out=self.c_819200)

    def time_double_subtract_1048576(self):
        np.subtract(self.a_1048576, self.b_1048576, out=self.c_1048576)

    def time_double_subtract_2097152(self):
        np.subtract(self.a_2097152, self.b_2097152, out=self.c_2097152)

    def time_double_subtract_4194304(self):
        np.subtract(self.a_4194304, self.b_4194304, out=self.c_4194304)

    def time_double_subtract_8388608(self):
        np.subtract(self.a_8388608, self.b_8388608, out=self.c_8388608)

    def time_double_multiply_0000096(self):
        np.multiply(self.a_96, self.b_96, out=self.c_96)

    def time_double_multiply_0000192(self):
        np.multiply(self.a_192, self.b_192, out=self.c_192)

    def time_double_multiply_0000384(self):
        np.multiply(self.a_384, self.b_384, out=self.c_384)

    def time_double_multiply_0000768(self):
        np.multiply(self.a_768, self.b_768, out=self.c_768)

    def time_double_multiply_0001024(self):
        np.multiply(self.a_1024, self.b_1024, out=self.c_1024)

    def time_double_multiply_0002048(self):
        np.multiply(self.a_2048, self.b_2048, out=self.c_2048)

    def time_double_multiply_0004096(self):
        np.multiply(self.a_4096, self.b_4096, out=self.c_4096)

    def time_double_multiply_0008192(self):
        np.multiply(self.a_8192, self.b_8192, out=self.c_8192)

    def time_double_multiply_0010240(self):
        np.multiply(self.a_10240, self.b_10240, out=self.c_10240)

    def time_double_multiply_0020480(self):
        np.multiply(self.a_20480, self.b_20480, out=self.c_20480)

    def time_double_multiply_0040960(self):
        np.multiply(self.a_40960, self.b_40960, out=self.c_40960)

    def time_double_multiply_0081920(self):
        np.multiply(self.a_81920, self.b_81920, out=self.c_81920)

    def time_double_multiply_0102400(self):
        np.multiply(self.a_102400, self.b_102400, out=self.c_102400)

    def time_double_multiply_0204800(self):
        np.multiply(self.a_204800, self.b_204800, out=self.c_204800)

    def time_double_multiply_0409600(self):
        np.multiply(self.a_409600, self.b_409600, out=self.c_409600)

    def time_double_multiply_0819200(self):
        np.multiply(self.a_819200, self.b_819200, out=self.c_819200)

    def time_double_multiply_1048576(self):
        np.multiply(self.a_1048576, self.b_1048576, out=self.c_1048576)

    def time_double_multiply_2097152(self):
        np.multiply(self.a_2097152, self.b_2097152, out=self.c_2097152)

    def time_double_multiply_4194304(self):
        np.multiply(self.a_4194304, self.b_4194304, out=self.c_4194304)

    def time_double_multiply_8388608(self):
        np.multiply(self.a_8388608, self.b_8388608, out=self.c_8388608)

    def time_double_divide_0000096(self):
        np.divide(self.a_96, self.b_96, out=self.c_96)

    def time_double_divide_0000192(self):
        np.divide(self.a_192, self.b_192, out=self.c_192)

    def time_double_divide_0000384(self):
        np.divide(self.a_384, self.b_384, out=self.c_384)

    def time_double_divide_0000768(self):
        np.divide(self.a_768, self.b_768, out=self.c_768)

    def time_double_divide_0001024(self):
        np.divide(self.a_1024, self.b_1024, out=self.c_1024)

    def time_double_divide_0002048(self):
        np.divide(self.a_2048, self.b_2048, out=self.c_2048)

    def time_double_divide_0004096(self):
        np.divide(self.a_4096, self.b_4096, out=self.c_4096)

    def time_double_divide_0008192(self):
        np.divide(self.a_8192, self.b_8192, out=self.c_8192)

    def time_double_divide_0010240(self):
        np.divide(self.a_10240, self.b_10240, out=self.c_10240)

    def time_double_divide_0020480(self):
        np.divide(self.a_20480, self.b_20480, out=self.c_20480)

    def time_double_divide_0040960(self):
        np.divide(self.a_40960, self.b_40960, out=self.c_40960)

    def time_double_divide_0081920(self):
        np.divide(self.a_81920, self.b_81920, out=self.c_81920)

    def time_double_divide_0102400(self):
        np.divide(self.a_102400, self.b_102400, out=self.c_102400)

    def time_double_divide_0204800(self):
        np.divide(self.a_204800, self.b_204800, out=self.c_204800)

    def time_double_divide_0409600(self):
        np.divide(self.a_409600, self.b_409600, out=self.c_409600)

    def time_double_divide_0819200(self):
        np.divide(self.a_819200, self.b_819200, out=self.c_819200)

    def time_double_divide_1048576(self):
        np.divide(self.a_1048576, self.b_1048576, out=self.c_1048576)

    def time_double_divide_2097152(self):
        np.divide(self.a_2097152, self.b_2097152, out=self.c_2097152)

    def time_double_divide_4194304(self):
        np.divide(self.a_4194304, self.b_4194304, out=self.c_4194304)

    def time_double_divide_8388608(self):
        np.divide(self.a_8388608, self.b_8388608, out=self.c_8388608)
