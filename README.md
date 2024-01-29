# KlemmUI Examples

Examples for the [KlemmUI UI library](https://github.com/Klemmbaustein/KlemmUI).

## Examples

| Name         | Description                                     |
|--------------|-------------------------------------------------|
| HelloWorld   | Creates a window with the title "Hello, World!" |
| Timer        | A simple timer app that measures time.          |
| Calculator   | A calculator app.                               |


## Building the examples

### Windows

Visual Studio 2022 with the "Desktop developement with C++" workload is required.

1. Run setup.ps1 in the Developer Powershell.


2.  Either:
    a): Open KlemmUIExamples.sln in Visual Studio and build the examples.

    b): Or Run `MSBuild KlemmUIExamples.sln -target:{Example to build}` in the Developer Powershell/Command Prompt.

### Linux

[KlemmBuild](https://github.com/Klemmbaustein/KlemmBuild) is required to build the examples on Linux.

1. Run [`setup.sh`]().
1. 