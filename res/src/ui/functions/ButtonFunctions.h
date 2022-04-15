#pragma once

#include <string>
#include <functional>
#include <vector>
#include "../../managers/SceneManager.h"

using std::string;
using std::to_string;
using std::function;
using std::out_of_range;
using std::vector;
using std::endl;
using std::cerr;

//In scene file: ChangeView [scene name]
struct VOID{
    void operator()(const vector<string>& nameAndArgs);
};

struct ChangeScene{
    void operator()(const vector<string>& nameAndArgs);
};

//In scene file: ChangeImage [scene name] [image name] [new image name or file location]
struct ChangeImage{
    void operator()(const vector<string>& nameAndArgs);
};

//In scene file: CycleImages [scene name] [image name] [starting image index] _files_
struct CycleImages{
    void operator()(vector<string>& nameAndArgs);
};

function<void(vector<string>&)> getFunction(const vector<string>& nameAndArgs);