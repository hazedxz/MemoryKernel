# GoldSrc Research Framework

## Overview

This repository provides a modular research framework for analyzing and interfacing with the GoldSrc engine runtime. The objective is to establish a standardized set of headers, mathematical primitives, and interface definitions that allow for the deep introspection of engine memory, rendering pipelines, and game logic.

## Legal and Academic Disclaimer

This project is intended strictly for educational and research purposes. The author assumes no liability for the implementation or use of this code. Users are responsible for complying with all applicable software policies and local laws. All interactions with third-party software environments are performed entirely at the user's risk.

## Repository Structure

The framework is organized into functional modules to isolate engine subsystems:

- sdk: Contains the core interface definitions required to communicate with engine systems. This includes common definitions, game UI structures, and engine-specific hooks.

- vector: Provides the foundational mathematical primitives. This module handles coordinate systems, angle calculations, and 3D space orientation necessary for trajectory and projection logic.

- dll: Implements memory loading mechanisms. This subsystem handles the manual mapping of binaries directly into process memory, bypassing standard loading procedures.

- bass: Manages the integration of external audio libraries within the engine context, facilitating the execution of sounds without reliance on the external filesystem.

## Prerequisites

This framework is designed for developers with advanced proficiency in the following areas:

- C++ Memory Management: Proficiency in pointers, custom memory layouts, and allocation logic.

- Reverse Engineering: Ability to identify function signatures, memory patterns, and hook points within the target process.

- Windows Systems Programming: Familiarity with the Windows API, particularly regarding process injection and memory protection.

## Implementation Guidelines

This repository provides the tools required to build custom features. It is not a turnkey solution. Successful implementation requires the user to bridge these definitions with the specific target runtime, identifying appropriate entry points and hook addresses manually. Contributions regarding engine accuracy and documentation improvements are welcome.
