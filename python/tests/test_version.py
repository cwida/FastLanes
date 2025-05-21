# python/tests/test_version.py

import pyfastlanes

def test_get_version():
    version = pyfastlanes.get_version()
    print("-- version : {}".format(version))
    assert isinstance(version, str)
    assert len(version) > 0
