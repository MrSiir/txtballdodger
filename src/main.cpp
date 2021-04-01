////////////////////////////////////////////////////
// * TXTBallDodger 2021
// * A Mini-Game example
//
// Copyright 2021 Francisco J. Gallego-Durán
//                @FranGallegoBR (fjgallego@ua.es)
//
// MIT LICENSE
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
////////////////////////////////////////////////////
//
// These are the contents of several cpp/hpp files
// in one single file. The contents of each file
// are tagged as "FILE: xxxxx" in case you wanted to
// copy it to your filesystem and use your own compilers.
//
// Tested under GCC 10.2 and CLANG 11.0.1
//
// You may also find the complete project, along with
// its makefile here:
// https://archive.org/details/txtballdodger-UA-2021
////////////////////////////////////////////////////
#include "world.hpp"
#include "tree/tree.hpp"

DecisionTree_t
createTree() {
    DecisionTree_t dt { 5 };

    auto& moveLeft = dt.createNode<ActionMove_t>(DIR_t::left);
    auto& moveRight = dt.createNode<ActionMove_t>(DIR_t::right);
    auto& idle = dt.createNode<ActionIdle_t>();

    auto& nodeMove = dt.createNode<NodeMove_t>(moveLeft, moveRight);
    dt.createNode<NodeIamSafe_t>(idle, nodeMove);

    return dt;
}

int main() {
    using namespace std::chrono_literals;

    auto tree { createTree() };
    World_t w(tree, 16ms);
    w.run();

    return 0;
}