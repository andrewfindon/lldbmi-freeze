# Recreation of vscode-cpptools Issue

A recreation of an issue encountered when using the VSCode c++ extension (https://github.com/microsoft/vscode-cpptools).

lldb-mi freezes (100% cpu and 20GB+ memory explosion) on MacOS, when breaking in certain places.

In this example it seems that lldb may be trying to resolve the values of an `initializer_list` that hasn't been initialised yet.

Breaking on any line inside of `freeze_up()` prior to the variable being initialised will trigger this issue.  Therefore breaking on line 6 will cause a freeze, but on line 7 is fine.

The issue occurs on both Intel and Apple Silicon (via Rossetta).

## Instructions

Build using:

`clang++ main.cpp -arch x86_64 -std=c++17 -g -o freeze`

(or use the VSCode build task).

Debug using the c++ extension.

## VSCode Logging

Tail of log at the point of a freeze:

```
--> E (stopped): {"type":"event","event":"stopped","body":{"reason":"step","threadId":1,"allThreadsStopped":true,"source":{"name":"main.cpp","path":"/Users/andrewfindon/Documents/lldbmi-crash/main.cpp","sources":[],"checksums":[]},"line":6,"column":1},"seq":641}
<--   C (threads-12): {"command":"threads","type":"request","seq":12}
--> R (threads-12): {"type":"response","request_seq":12,"success":true,"command":"threads","body":{"threads":[{"id":1,"name":"Thread #1"}]},"seq":644}
<--   C (stackTrace-13): {"command":"stackTrace","arguments":{"threadId":1,"startFrame":0,"levels":20},"type":"request","seq":13}
--> R (stackTrace-13): {"type":"response","request_seq":13,"success":true,"command":"stackTrace","body":{"stackFrames":[{"id":1000,"name":"freeze!freeze_up()","source":{"name":"main.cpp","path":"/Users/andrewfindon/Documents/lldbmi-crash/main.cpp","sources":[],"checksums":[]},"line":6,"column":1,"moduleId":1},{"id":1001,"name":"freeze!main","source":{"name":"main.cpp","path":"/Users/andrewfindon/Documents/lldbmi-crash/main.cpp","sources":[],"checksums":[]},"line":12,"column":1,"moduleId":1},{"id":1002,"name":"libdyld.dylib!start","line":0,"column":0,"moduleId":12},{"id":1003,"name":"libdyld.dylib!start","line":0,"column":0,"moduleId":12}],"totalFrames":4},"seq":647}
<--   C (scopes-14): {"command":"scopes","arguments":{"frameId":1000},"type":"request","seq":14}
--> E (output): {"type":"event","event":"output","body":{"category":"console","output":"1: (33618) <-1018-stack-list-variables 0 --thread 1 --frame 0\n"},"seq":650}
1: (33618) <-1018-stack-list-variables 0 --thread 1 --frame 0
--> E (output): {"type":"event","event":"output","body":{"category":"console","output":"1: (33631) ->1018^done,variables=[{name=\"bad_var\"}]\n"},"seq":652}
1: (33631) ->1018^done,variables=[{name="bad_var"}]
--> E (output): {"type":"event","event":"output","body":{"category":"console","output":"1: (33631) ->(gdb)\n"},"seq":654}
1: (33631) ->(gdb)
--> E (output): {"type":"event","event":"output","body":{"category":"console","output":"1: (33632) 1018: elapsed time 13\n"},"seq":656}
1: (33632) 1018: elapsed time 13
--> E (output): {"type":"event","event":"output","body":{"category":"console","output":"1: (33657) <-1019-var-create - - \"bad_var\" --thread 1 --frame 0\n"},"seq":658}
1: (33657) <-1019-var-create - - "bad_var" --thread 1 --frame 0
```
