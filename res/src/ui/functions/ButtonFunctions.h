#pragma once

#include <string>
#include <functional>
#include <vector>
#include "../../managers/SceneManager.h"
#include "../../python/PythonScript.h"

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

//In scene file: CycleImagesFwd [scene name] [image name] [linked button name] [starting image index] [_FILES_/_COMPRESSED FILES_]
struct CycleImagesFwd{
    void operator()(vector<string>& nameAndArgs);
};

//In scene file: CycleImagesRev [scene name] [image name] [linked button name] [starting image index] [_FILES_/_COMPRESSED FILES_]
struct CycleImagesRev{
    void operator()(vector<string>& nameAndArgs);
};

//In scene file: Compress [input text box name] [linked checkbox name #1] [linked checkbox name #2] ...
struct Compress{
    void operator()(vector<string>& nameAndArgs);
};

//In scene file: SelectSize [size label] [linked checkbox name #1] [linked checkbox name #2] ...
struct SelectSize{
    void operator()(vector<string>& nameAndArgs);
};

function<void(vector<string>&)> getFunction(vector<string>& nameAndArgs);