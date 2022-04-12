#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <set>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/eval.h>
#include <pybind11/numpy.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

namespace py = pybind11;
namespace fs = std::filesystem;

using std::string;
using std::cerr;
using std::set;
using std::vector;
using fs::exists;
using py::eval_file;
using py::object;
using py::module_;
using py::scoped_interpreter;

//Runs a simple python file with no arguments or libraries.
void runPy(const string& fileLocation);

//Runs a python file with numpy library.
void runPy(const string& fileLocation, set<string>& files);