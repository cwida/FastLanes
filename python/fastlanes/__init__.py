# python/fastlanes/__init__.py
from ._fastlanes import get_version, __doc__ as _doc

__doc__ = _doc  # Export C++ module docstring to package level

__all__ = ["get_version"]
