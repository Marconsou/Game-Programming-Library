#ifndef BUILDDLL_H
#define BUILDDLL_H

#ifdef GAMEPROGRAMMINGLIBRARY_EXPORTS
#define GPL_DLL __declspec(dllexport)
#else
#define GPL_DLL __declspec(dllimport)
#endif

#endif