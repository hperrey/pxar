################################################
#                 WARNING!                     #
# This file has been auto-generated by xdress. #
# Do not modify!!!                             #
#                                              #
#                                              #
#                    Come on, guys. I mean it! #
################################################


cimport numpy as np
cimport xdress_extra_types
from libcpp.map cimport map as cpp_map
from libcpp.vector cimport vector as cpp_vector
from pyPxarCore cimport c_api



cdef class tbmConfig:
    cdef void * _inst
    cdef public bint _free_inst
    cdef public stlcontainers._MapUCharUChar _dacs
    pass





cdef class pixelConfig:
    cdef void * _inst
    cdef public bint _free_inst
    pass





cdef class api:
    cdef void * _inst
    cdef public bint _free_inst
    pass





cdef class rocConfig:
    cdef void * _inst
    cdef public bint _free_inst
    cdef public stlcontainers._MapUCharUChar _dacs
    cdef public np.ndarray _pixels
    pass





cdef class dut:
    cdef void * _inst
    cdef public bint _free_inst
    pass





cdef class pixel:
    cdef void * _inst
    cdef public bint _free_inst
    pass




