# python/tests/test_version.py

import fastlanes

def test_get_version():
    version = fastlanes.get_version()
    assert isinstance(version, str)
    assert len(version) > 0
