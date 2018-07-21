
"""
utility for generating numpy vectors for randomized test data
"""

import numpy as np

def make_vec(size=2, max=1.0, min=-1.0):
    assert max > min
    diff = max - min
    return (np.random.rand(size) * diff) + min
