# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# python/pyfastlanes/__init__.py
# ────────────────────────────────────────────────────────
"""
PyFastLanes Python API
"""

try:
    from ._fastlanes import (
        get_version,
        Connection,
        connect,
        # Add any other bindings you expose here
    )
except ImportError:  # pragma: no cover - fallback for missing extension
    def get_version() -> str:
        """Return a placeholder version when the C++ extension is unavailable."""

        return "0.0.0"

    class Connection:  # type: ignore
        """Dummy placeholder for the native :class:`Connection` class."""

        def __init__(self, *args, **kwargs) -> None:  # pragma: no cover - runtime
            raise ImportError(
                "pyfastlanes C++ extension is not built; install from source "
                "or build the extension to use this functionality"
            )

    def connect() -> Connection:
        """Return a :class:`Connection` instance using the fallback."""

        return Connection()

__all__ = [
    "get_version",
    "Connection",
    "connect",
    # Add others as needed
]
