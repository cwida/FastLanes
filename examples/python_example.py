#!/usr/bin/env python3
import fastlanes

def main():
    # 1) Print the module docstring
    print(fastlanes.__doc__)

    # 2) Call your free helper
    version = fastlanes.get_version()
    print(f"FastLanes version: {version}")

if __name__ == "__main__":
    main()
